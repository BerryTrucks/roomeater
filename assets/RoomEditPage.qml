import bb.cascades 1.4

Sheet {
    id: editRoom
    objectName: "editRoom"
    property string roomId: ""
    property string building: ""
    property string capacity: ""
    property string floor: ""
    property string number: ""
    property bool hasShower: false
    property bool inEditMode: true
    function setHash(hash){
        roomId = hash
    }
    function setBulding(b){
        editRoom.building = b
    }
    function setCapacity(cap){
        editRoom.capacity = cap
    }
    function setFloor(fl){
        editRoom.floor = fl
    }
    function setNumber(num){
        editRoom.number = num
    }
    function setHasShower(shower){
        editRoom.hasShower = shower
    }
    function loadDataToFields(){
        editRoom.inEditMode = true;
        title.text = qsTr("Edit room nr %1 on %2 floor in %3 building").arg(number).arg(floor).arg(building);
        buildingTbx.text = building;
        capacityTbx.text = capacity;
        floorTbx.text = floor;
        numberTbx.text = number;
        showerToggle.checked = hasShower;
    }
    function prepareForNew(){
        editRoom.inEditMode = false;
        title.text = "Create new room";
    }
    content: Page {
        actions: [
            ActionItem {
                id: cancel
                title: "cancel"
                imageSource: "images/cancel.png"
                ActionBar.placement: ActionBarPlacement.Signature
                onTriggered: {
                    close();
                }
            },
            ActionItem {
                id: save
                title: "Save"
                imageSource: "images/add.png"
                ActionBar.placement: ActionBarPlacement.Signature
                onTriggered: {
                    if (editRoom.inEditMode){
                        bValidator.validate();
                        cValidator.validate();
                        nValidator.validate();
                        if ((bValidator.state == ValidationState.Valid && cValidator.state == ValidationState.Valid && nValidator.state == ValidationState.Valid) || 
                        (bValidator.state == ValidationState.Unknown && cValidator.state == ValidationState.Unknown && nValidator.state == ValidationState.Unknown)){
                            _room.updateAndSaveRoom(roomId, buildingTbx.text, capacityTbx.text, floorTbx.text, numberTbx.text, showerToggle.checked)
                            close();
                        }             
                    } else {
                        bValidator.validate();
                        cValidator.validate();
                        nValidator.validate();                        
                        if ((bValidator.state == ValidationState.Valid && cValidator.state == ValidationState.Valid && nValidator.state == ValidationState.Valid) || 
                        (bValidator.state == ValidationState.Unknown && cValidator.state == ValidationState.Unknown && nValidator.state == ValidationState.Unknown)){
                            _room.updateAndSaveRoom("", buildingTbx.text, capacityTbx.text, floorTbx.text, numberTbx.text, showerToggle.checked)
                            close();
                        }
                    }
                }
            }
        ]
        Container {
            layout: StackLayout {}
            topMargin: 10.0
            bottomMargin: 10.0
            bottomPadding: 10.0
            topPadding: 10.0
            leftPadding: 10.0
            rightPadding: 10.0
            layoutProperties: AbsoluteLayoutProperties {}
            Container {
                bottomPadding: 10.0
                topPadding: 10.0
                horizontalAlignment: HorizontalAlignment.Center
                Label {
                    id: title
                    text: "Edit room"
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                bottomPadding: 10.0
                topPadding: 10.0
                Label {
                    id: buildingLbl
                    text: "Building"
                    verticalAlignment: VerticalAlignment.Center
                }
                TextField {
                    id: buildingTbx
                    text: qsTr("%1").arg(building)
                    validator: Validator {
                        id: bValidator
                        mode: ValidationMode.Immediate | ValidationMode.FocusLost
                        errorMessage: "Building name has to be representitive"
                        onValidate: {
                            if (buildingTbx.text.length < 1){
                                state = ValidationState.Invalid
                            }
                        }
                    }
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                bottomPadding: 10.0
                topPadding: 10.0
                Label {
                    id: capacityLbl
                    text: "Capacity"
                    verticalAlignment: VerticalAlignment.Center
                }
                TextField {
                    id: capacityTbx
                    inputMode: TextFieldInputMode.Pin
                    text: qsTr("%1").arg(capacity)
                    validator: Validator {
                        id: cValidator
                        mode: ValidationMode.Immediate | ValidationMode.FocusLost
                        errorMessage: "Capacity has to be a number greater than 0"
                        onValidate: {
                            if (capacityTbx.text.length < 1){
                                state = ValidationState.Invalid
                            }
                            if (!capacityTbx.text.match("^[0-9]*$")){
                                state = ValidationState.Invalid
                            }
                        }
                    }
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                bottomPadding: 10.0
                topPadding: 10.0
                Label {
                    id: floorLbl
                    text: "Floor"
                    verticalAlignment: VerticalAlignment.Center
                }
                TextField {
                    id: floorTbx
                    inputMode: TextFieldInputMode.Pin
                    text: qsTr("%1").arg(floor)
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                bottomPadding: 10.0
                topPadding: 10.0
                Label {
                    id: numberLbl
                    text: "Number"
                    verticalAlignment: VerticalAlignment.Center
                }
                TextField {
                    id: numberTbx
                    inputMode: TextFieldInputMode.Pin
                    text: qsTr("%1").arg(number)
                    validator: Validator {
                        id: nValidator
                        mode: ValidationMode.Immediate | ValidationMode.FocusLost
                        errorMessage: "Room number has to be a numeric value"
                        onValidate: {
                            if (numberTbx.text.length < 1){
                                state = ValidationState.Invalid
                            }
                            if (!numberTbx.text.match("^[0-9]*$")){
                                state = ValidationState.Invalid
                            }
                        }
                    }
                }
            }
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                bottomPadding: 10.0
                topPadding: 10.0
                Label {
                    id: showerLbl
                    text: "Has shower"
                    verticalAlignment: VerticalAlignment.Center
                }
                ToggleButton {
                    id: showerToggle
                    checked: false
                }
            }
        }
    }
}
