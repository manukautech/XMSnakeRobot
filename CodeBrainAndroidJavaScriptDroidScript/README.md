This Snake Robot has an Android device for a "brain".   
This communicates with the "spinal cord", an HC-05 module and 3 x Arduino Nanos, via Bluetooth.

App Programming is in the "DroidScript" framework and environment. 
The coding languages are HTML and JavaScript.
The App is under container folder "XMSnakeV07". The main code file is "XMSnakeV07.html".
The "Gaits" or movements are coded as arrays of servo angles in files "Gait01.js", "Gait02.js" etc

"XMSnakeV07.html" looks like a conventional web page with JavaScript and it will display in a browser.  
There are only 3 lines of code that make it an Android App by relating it to the DroidScript framework.  
This framework then adds a JavaScript API for phone resources, in this case Bluetooth.  
The one line of code to get started with Bluetooth is:  
<code>bt = app.CreateBluetoothSerial();</code>  

"Servo-Inchworm_Gait_Worksheet.pdf" is a scan of my worksheet for getting started with coding the "inchworm gait" in  "XMSnakeBrain.html".  Drawing diagrams of a workable pulse travelling from tail to head soon revealed a pattern of angles like:
... 0, -40, 40, 40, -40, 0 ...
See this implemented in "Gait05.js" 
"Gait01.js" is the current standard rectilinear movement. It improves on "Gait05.js" by running 2 x ripple pulses along the snake body.

"XMSnakeRobot-Servo-Worksheet.docx" is a blank gait worksheet.

"DroidScript" has some similarities to Apache Cordova but it is simpler and lighter because it only targets Android. The IDE runs on the Android device and tests the resulting code there. The IDE can be remote controlled from a laptop or full size computer giving a big screen editing experience. I selected "DroidScript" after extensively evaluating frameworks - details about that at:  
<a href="https://hitechfromlotech.blogspot.co.nz/2017/01/">https://hitechfromlotech.blogspot.co.nz/2017/01/</a>  
  
"DroidScript" is a free app from the Google Play App store.  
<a href="https://play.google.com/store/apps/details?id=com.smartphoneremote.androidscriptfree&hl=en">https://play.google.com/store/apps/details?id=com.smartphoneremote.androidscriptfree&hl=en</a>  
  
