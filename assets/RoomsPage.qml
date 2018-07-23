import bb.cascades 1.4


Page {
    Container {
        id: container
        objectName: "container"
        ListView {
            id: roomListView
            objectName: "roomListView" 
            dataModel: _room.dataModel
            property string swapFrom: ""
            property Sheet roomEditSheet: null
            multiSelectAction: MultiSelectActionItem {
                multiSelectHandler: roomListView.multiSelectHandler
            }
            multiSelectHandler{
                status: "0 rooms selected"
                actions: [
                    ActionItem {
                        title: "Available"
                        onTriggered: {
                            var selectionList = roomListView.selectionList();
                            roomListView.clearSelection();
                            for (var i = 0; i < selectionList.length; i++){
                                console.log(roomListView.dataModel.data(selectionList[i]).hash)
                                roomListView.setAvailability(true, roomListView.dataModel.data(selectionList[i]).hash);                                
                            }
                        }
                    },
                    ActionItem {
                        title: "Unavailable"
                        onTriggered: {
                            var selectionList = roomListView.selectionList();
                            roomListView.clearSelection();
                            for (var i = 0; i < selectionList.length; i++){
                                console.log(roomListView.dataModel.data(selectionList[i]).hash)
                                roomListView.setAvailability(false, roomListView.dataModel.data(selectionList[i]).hash);                                      
                            }
                        }
                    },
                    ActionItem {
                        title: "Remove rooms"
                        onTriggered: {
                            var selectionList = roomListView.selectionList();
                            roomListView.clearSelection();
                            for (var i = 0; i < selectionList.length; i++){
                                console.log(roomListView.dataModel.data(selectionList[i]).hash)
                                roomListView.remove(roomListView.dataModel.data(selectionList[i]).hash);                                      
                            }
                        }
                    }
                ]
            }
            onSelectionChanged: {
                roomListView.multiSelectHandler.status = roomListView.selectionList().length + " rooms selected";
            }
            listItemComponents: ListItemComponent {
                    type: "item"
                    StandardListItem {
                        id: stdItem
                        title: qsTr("Room nr %1 on %2 floor\t%3").arg(ListItemData.roomNumber).arg(ListItemData.floor).arg(ListItemData.avail)
                        status: qsTr("%1 (%2/%3)").arg(ListItemData.build).arg(ListItemData.peopleIn).arg(ListItemData.capacity)
                        description: ListItemData.people
                        imageSource: "images/" + ListItemData.standard
                        contextActions: [
                            ActionSet {
//                                ActionItem {
//                                    title: "Edit room info";
//                                    onTriggered: {                                        
//                                        var myView = stdItem.ListItem.view;
//                                        var dataModel = myView.dataModel;
//                                        var indexPath = myView.selected();
//                                        stdItem.ListItem.view.openRoomDetails(dataModel.data(indexPath).hash, dataModel.data(indexPath).build, dataModel.data(indexPath).capacity, dataModel.data(indexPath).floor, dataModel.data(indexPath).roomNumber, dataModel.data(indexPath).standard);
//                                    }
//                                }
                                ActionItem {
                                    title: "Swap people"
                                    onTriggered: {
                                        var myView = stdItem.ListItem.view;
                                        var dataModel = myView.dataModel;
                                        var indexPath = myView.selected();                                        
                                        stdItem.ListItem.view.swapFrom = dataModel.data(indexPath).hash;
                                    }                                    
                                }
                                DeleteActionItem {
                                    title: "Remove room"
                                    onTriggered: {
                                        var myView = stdItem.ListItem.view;
                                        var dataModel = myView.dataModel;
                                        var indexPath = myView.selected(); 
                                        stdItem.ListItem.view.remove(dataModel.data(indexPath).hash); 
                                    }
                                }
                                ActionItem {
                                    title: "Free up"
                                    onTriggered: {
                                        var myView = stdItem.ListItem.view;
                                        var dataModel = myView.dataModel;
                                        var indexPath = myView.selected();
                                        console.log(indexPath); 
                                        stdItem.ListItem.view.freeUp(dataModel.data(indexPath).hash);                                        
                                    }
                                }
                                ActionItem {
                                    title: "Drop everyone // todo"
                                    onTriggered: {                                                                                
                                    }
                                }
                                ActionItem {
                                    title: "Available"
                                    onTriggered: {
                                        var myView = stdItem.ListItem.view;
                                        var dataModel = myView.dataModel;
                                        var indexPath = myView.selected(); 
                                        stdItem.ListItem.view.setAvailability(true, dataModel.data(indexPath).hash);                                        
                                    }
                                }
                                ActionItem {
                                    title: "Unavailable"
                                    onTriggered: {
                                        var myView = stdItem.ListItem.view;
                                        var dataModel = myView.dataModel;
                                        var indexPath = myView.selected(); 
                                        stdItem.ListItem.view.setAvailability(false, dataModel.data(indexPath).hash);                                        
                                    }
                                }
                            }
                        ]
                    }
            }
            onCreationCompleted: {
                _room.updateView();
            }
            onTriggered: {
                roomListView.clearSelection();
                select(indexPath);
                if (swapFrom !== ""){
                    var temp = swapFrom;
                    swapFrom = "";
                    swap(temp, dataModel.data(indexPath).hash);
                } else {                    
                    openRoomDetails(dataModel.data(indexPath).hash, dataModel.data(indexPath).build, dataModel.data(indexPath).capacity, dataModel.data(indexPath).floor, dataModel.data(indexPath).roomNumber, dataModel.data(indexPath).standard);
                }
            }
            attachedObjects: [                
                ComponentDefinition {
                    id: roomEditView
                    source: "RoomEditPage.qml"
                }
            ]
            function openRoomDetails(hash, building, capacity, floor, number, shower){
                roomEditSheet = roomEditView.createObject(roomsPage);
                roomEditSheet.setHash(hash);
                roomEditSheet.setBulding(building);
                roomEditSheet.setCapacity(capacity);
                roomEditSheet.setFloor(floor);
                roomEditSheet.setNumber(number);
                roomEditSheet.setHasShower(shower == "room_with_shower.png" ? true : false);
                roomEditSheet.loadDataToFields();
                roomEditSheet.open();
            }
            function freeUp(hash){           
                _room.freeUp(hash);
            }
            function remove(hash){
                _room.remove(hash);
            }
            function setAvailability(state, hash){
                if (state == true){
                    _room.makeAvailable(hash);
                }else{
                    _room.makeUnavailable(hash);
                }                
            }
            function swap(from, to){
                if (from !== to)
                {
                    _room.swap(from, to);
                }
            }
        }
    }
    id: roomsPage
    objectName: "roomsPage"
    actionBarAutoHideBehavior: ActionBarAutoHideBehavior.HideOnScroll
    actions: [
        ActionItem {
            id: addRoom
            title: "Add room"
            imageSource: "images/add.png"
            ActionBar.placement: ActionBarPlacement.Signature
            onTriggered: {
                roomListView.roomEditSheet = roomEditView.createObject(this);
                roomListView.roomEditSheet.prepareForNew();
                roomListView.roomEditSheet.open();
            }
        }
    ]
}