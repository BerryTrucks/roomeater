import bb.cascades 1.4

Sheet {
    id: assignPerson
    objectName: "assignPerson"
    property string userId: ""
    property string userName: ""
    function initialize (id){
        userId = id;
    }
    function setUserName(fullName){
        userName = fullName;
    }
    content: Page {        
        actionBarAutoHideBehavior: ActionBarAutoHideBehavior.HideOnScroll
        actions: [
            ActionItem {
                id: cancel
                title: "Cancel"
                imageSource: "images/cancel.png"
                ActionBar.placement: ActionBarPlacement.Signature
                onTriggered: {
                    close();
                }
            }
        ]
        Container {
            id: container
            objectName: "container"
            Label {
                text: qsTr("Assign %1 to").arg(userName);
            }
            ListView {
                id: roomListView
                objectName: "roomListView" 
                dataModel: _room.availableRoomsDataModel
                listItemComponents: ListItemComponent {
                    type: "item"
                    StandardListItem {
                        id: stdItem
                        title: qsTr("Room nr %1 on %2 floor\t%3").arg(ListItemData.roomNumber).arg(ListItemData.floor).arg(ListItemData.avail)
                        status: qsTr("%1 %2").arg(ListItemData.build).arg(ListItemData.capacity)
                        description: ListItemData.people
                        imageSource: "images/" + ListItemData.standard
                    }
                }
                onCreationCompleted: {
                    _room.updateAvailableRoomsView();
                }
                onTriggered: {
                    roomListView.clearSelection();
                    select(indexPath);
                    if (userId !== ""){
                        assignPersonToRoom(userId, dataModel.data(indexPath).hash);
                    }
                    close();
                }
                function assignPersonToRoom(personId, roomId){           
                    _mediator.assignPersonToRoom(personId, roomId);
                }
            }
        }
    }
}
