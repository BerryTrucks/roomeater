import bb.cascades 1.4

Container {
    id: refreshContainer    
    ListView {
        id: peopleListView
        objectName: "peopleListView"
        dataModel: _people.dataModel
        property Sheet roomsCandidate: null
        leadingVisual: DropDown {
            id: solutionOption
            objectName: "solutionOption"
            title: "Algorithm"
            Option {
                text: "Naive min value"
                description: "The lowest value from the bottom of the priority list"
            }
            Option {
                text: "Naive max value"
                description: "The highest value from the top of the priority list"
            }
            Option {
                text: "Naive min/max value"
                description: "The highest from the top, the lowest from the bottom of the priority list"
            }
            Option {
                text: "Naive max value - couples take only 2 person room"
                description: "max value + couple preferably to 2 person room"
                selected: true;
            }
            Option {
                text: "Naive max value - couples fill room"
                description: "max value + couple preferably to even capacity room"
            }
            onSelectedIndexChanged: {
                _app.setSolver(selectedIndex);
            }
        }
        multiSelectAction: MultiSelectActionItem {
            multiSelectHandler: peopleListView.multiSelectHandler;
        }
        multiSelectHandler{
            actions: [
                ActionItem {
                    title: "Drop from rooms"
                    onTriggered: {
                        var selectionList = peopleListView.selectionList();
                        peopleListView.clearSelection()
                        for (var i = 0; i < selectionList.length; i++){
                            peopleListView.unassign(peopleListView.dataModel.data(selectionList[i]).hash);
                        }
                    }
                },
                ActionItem {
                    title: "Assign to room //todo"
                }
            ]
        }
        listItemComponents: ListItemComponent {
            type: "item"                
            StandardListItem {
                id: stdItem
                title: qsTr("%1 %2").arg(ListItemData.firstName).arg(ListItemData.lastName) 
                description: ListItemData.spouse
                imageSource: "images/" + ListItemData.gender
                status: ListItemData.room
                contextActions: [
                    ActionSet {
                        ActionItem {
                            title: "Drop from room"
                            onTriggered: {
                                var myView = stdItem.ListItem.view;
                                var dataModel = myView.dataModel;
                                var indexPath = myView.selected(); 
                                stdItem.ListItem.view.unassign(dataModel.data(indexPath).hash);  
                            }
                        }
                        ActionItem {
                            title: "Assign to room"
                            onTriggered: {
                                var myView = stdItem.ListItem.view;
                                var dataModel = myView.dataModel;
                                var indexPath = myView.selected(); 
                                stdItem.ListItem.view.createRoomsPage(dataModel.data(indexPath).hash, qsTr("%1 %2").arg(dataModel.data(indexPath).firstName).arg(dataModel.data(indexPath).lastName));
                            }   
                        }
                    }
                ]
            }
        }
        onCreationCompleted: {
            _people.updateView();
        }
        onTriggered: {
            peopleListView.clearSelection();
            select(indexPath);
        }
        attachedObjects: [
            ListScrollStateHandler {                    
                id: listScrollHandler                    
            },
            ComponentDefinition {
                id: availableRooms
                source: "AssignPersonToRoom.qml"
            }
        ]
        function createRoomsPage(personId, personName){
            roomsCandidate = availableRooms.createObject(refreshContainer);
            roomsCandidate.initialize(personId);
            roomsCandidate.setUserName(personName);
            roomsCandidate.open();
        }
        function unassign(hash){
            _people.unassign(hash);
        }
    }        
}