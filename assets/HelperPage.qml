import bb.cascades 1.4

Container {
    signal dataAvailable()
    id: containerHelper
    DropDown {
        title: "Historical data"
        Option {
            text: "11Jan14"
        }
        Option {
            text: "1Feb14"
        }
        Option {
            text: "8Feb14"
        }
        Option {
            text: "10Jan15"
        }
        Option {
            text: "7Feb15"
        }
        Option {
            text: "16Jan16"
            selected: true
        }
        Option {
            text: "23Jan16"
        }
        onSelectedIndexChanged: {
            _app.setDataFile(selectedOption.text);
        }
    }
    Divider {
        
    }
    Button {
        id: loadBtn
        horizontalAlignment: HorizontalAlignment.Fill
        objectName: "loadBtn"
        text: qsTr("Load data")
    }
    Button{
        id: clearBtn
        horizontalAlignment: HorizontalAlignment.Fill
        visible: false
        objectName: "clearBtn"
        text: qsTr("Clear")
        onClicked: {
            dataToParse.text = "";
        }
    }
    TextArea {
        id: dataToParse
        objectName: "dataToParse"
        minHeight: 400
        hintText: "Paste the priority list here"
        property bool signalSent: false;
        signal passDataToParse(string data)
        function updateWithOwnContent(){
            passDataToParse(dataToParse.text); //this has to be here for now
        }
        function updateContent(data){
            text = data
            passDataToParse(dataToParse.text); //this has to be here for now
            dataAvailable();
        }
    }
    function triggetParsing(){
        dataToParse.updateWithOwnContent();
    }
}