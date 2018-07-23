/*
 * Copyright (c) 2011-2015 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.4
import bb.system 1.2

NavigationPane{
    id: navPane
    Page{
        id: mainPage
        actionBarAutoHideBehavior: ActionBarAutoHideBehavior.HideOnScroll
        actions:[
            ActionItem {
                id: assign
                objectName: "assign"
                title: "Assign"
                imageSource: "images/assign.png"
                ActionBar.placement: ActionBarPlacement.Signature
                enabled: false
                signal onAction()
                onTriggered: {
                    activityInd.visible = true
                    if (!activityInd.running){
                        activityInd.start();
                        onAction()
                    }else {
                        root.activityDone();
                    }
                }
            },
            ActionItem {
                id: parse
                title: "Parse"
                imageSource: "images/parse.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                enabled: true // changed
                // TODO: this has to first get signal with data from textview to use this action
                onTriggered: {
                    mainView.source = peoplePage.source
                    mainView.visible = true;
                    enabled = false;
                    assign.enabled = true;
                    refHelperPage.visible = false;
                    refHelperPage.triggetParsing();
                }
            },
            ActionItem {
                id: editRooms
                title: "Show rooms"
                imageSource: "images/rooms.png"
                ActionBar.placement: ActionBarPlacement.OnBar
                onTriggered: {
                    var roomsPageObject = roomsPage.createObject();                    
                    navPane.push(roomsPageObject)
                }
            }
        ]
        attachedObjects: [
            ComponentDefinition {
                id: roomsPage
                source: "RoomsPage.qml"
            },
            ComponentDefinition {
                id: peoplePage
                source: "PeoplePage.qml"
            }
        ]
        
        Container {        
            id: root
            objectName: "root"
            ActivityIndicator {
                horizontalAlignment: HorizontalAlignment.Center
                id: activityInd
                objectName: "activityInd"
                visible: false
            }
            property string content;
            function showToast(message) {
                content = message;
                toast.show();
            }
            attachedObjects:[
                SystemToast {
                    id: toast
                    body: "" + root.content 
                    button.label: "Got it"
                    button.enabled: true                   
                }
            ]
            /**
             * This is simply to try out that way of showing pages
             * Equaly good would be use an object of PeoplePage the same
         * way HelperPage is used.
         */
        ControlDelegate { 
            id: mainView
            source: peoplePage.source
            visible:  false
        }
        HelperPage {
            id: refHelperPage
        }
        function activityDone(){
            activityInd.stop();
            activityInd.visible = false;
        }
    }
    
    function unlockActions(){
        parse.enabled = true;
    }
    onCreationCompleted: {
        console.log("Reached on completed")
        refHelperPage.dataAvailable.connect(unlockActions);
    }
    }
}