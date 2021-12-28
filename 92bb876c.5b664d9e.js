(window.webpackJsonp=window.webpackJsonp||[]).push([[38],{119:function(e,t,a){"use strict";a.d(t,"a",(function(){return b})),a.d(t,"b",(function(){return m}));var n=a(0),r=a.n(n);function i(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function o(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,n)}return a}function l(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?o(Object(a),!0).forEach((function(t){i(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):o(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function c(e,t){if(null==e)return{};var a,n,r=function(e,t){if(null==e)return{};var a,n,r={},i=Object.keys(e);for(n=0;n<i.length;n++)a=i[n],t.indexOf(a)>=0||(r[a]=e[a]);return r}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(n=0;n<i.length;n++)a=i[n],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(r[a]=e[a])}return r}var s=r.a.createContext({}),p=function(e){var t=r.a.useContext(s),a=t;return e&&(a="function"==typeof e?e(t):l(l({},t),e)),a},b=function(e){var t=p(e.components);return r.a.createElement(s.Provider,{value:t},e.children)},d={inlineCode:"code",wrapper:function(e){var t=e.children;return r.a.createElement(r.a.Fragment,{},t)}},u=r.a.forwardRef((function(e,t){var a=e.components,n=e.mdxType,i=e.originalType,o=e.parentName,s=c(e,["components","mdxType","originalType","parentName"]),b=p(a),u=n,m=b["".concat(o,".").concat(u)]||b[u]||d[u]||i;return a?r.a.createElement(m,l(l({ref:t},s),{},{components:a})):r.a.createElement(m,l({ref:t},s))}));function m(e,t){var a=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var i=a.length,o=new Array(i);o[0]=u;var l={};for(var c in t)hasOwnProperty.call(t,c)&&(l[c]=t[c]);l.originalType=e,l.mdxType="string"==typeof e?e:n,o[1]=l;for(var s=2;s<i;s++)o[s]=a[s];return r.a.createElement.apply(null,o)}return r.a.createElement.apply(null,a)}u.displayName="MDXCreateElement"},95:function(e,t,a){"use strict";a.r(t),a.d(t,"frontMatter",(function(){return o})),a.d(t,"metadata",(function(){return l})),a.d(t,"rightToc",(function(){return c})),a.d(t,"default",(function(){return p}));var n=a(2),r=a(6),i=(a(0),a(119)),o={id:"getting_started",title:"Getting Started",sidebar_label:"Getting Started",slug:"/"},l={unversionedId:"getting_started",id:"getting_started",isDocsHomePage:!1,title:"Getting Started",description:"BlueMicro Youtube Channel",source:"@site/docs/getting_started.md",slug:"/",permalink:"/docs/",editUrl:"https://github.com/jpconstantineau/BlueMicro_BLE/tree/documentation-docusaurus/documentation/docs/getting_started.md",version:"current",sidebar_label:"Getting Started",sidebar:"someSidebar",next:{title:"A DIY Friendly Firmware",permalink:"/docs/bluetooth_firmware"}},c=[{value:"BlueMicro Youtube Channel",id:"bluemicro-youtube-channel",children:[]},{value:"NEW: BlueMicro Builder",id:"new-bluemicro-builder",children:[]},{value:"Getting Started: in 4 simple steps",id:"getting-started-in-4-simple-steps",children:[{value:"Step 1: Option 1 - Install Arduino IDE",id:"step-1-option-1---install-arduino-ide",children:[]},{value:"Step 1: Option 2 - Install Arduino CLI (Windows script)",id:"step-1-option-2---install-arduino-cli-windows-script",children:[]},{value:"Step 2: Download BlueMicro_BLE Firmware",id:"step-2-download-bluemicro_ble-firmware",children:[]},{value:"Step 3: Edit 4 Keyboard Files",id:"step-3-edit-4-keyboard-files",children:[]},{value:"Step 4: Compile and Upload",id:"step-4-compile-and-upload",children:[]}]}],s={rightToc:c};function p(e){var t=e.components,a=Object(r.a)(e,["components"]);return Object(i.b)("wrapper",Object(n.a)({},s,a,{components:t,mdxType:"MDXLayout"}),Object(i.b)("h2",{id:"bluemicro-youtube-channel"},"BlueMicro Youtube Channel"),Object(i.b)("p",null,"See a number of tutorials, builds and other keyboard related videos on the ",Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://www.youtube.com/channel/UCFpGp4hHe03nvF9c8_gF_jA/featured"}),"BlueMicro Youtube Channel"),"."),Object(i.b)("h2",{id:"new-bluemicro-builder"},"NEW: BlueMicro Builder"),Object(i.b)("p",null,"A very easy way to get setup with your own firmware and compile it without installing anything on your computer",Object(i.b)("sup",Object(n.a)({parentName:"p"},{id:"fnref-1"}),Object(i.b)("a",Object(n.a)({parentName:"sup"},{href:"#fn-1",className:"footnote-ref"}),"1")),"! "),Object(i.b)("p",null,"More documentation to come...\nFind the builder ",Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://github.com/jpconstantineau/BlueMicro_Builder"}),"here")," and follow the instructions in the readme."),Object(i.b)("h2",{id:"getting-started-in-4-simple-steps"},"Getting Started: in 4 simple steps"),Object(i.b)("p",null,"Getting started with flashing your nRF52 board is as simple as installing the Arduino IDE for your operating system, adding the board support packages and compiling the firmware."),Object(i.b)("h3",{id:"step-1-option-1---install-arduino-ide"},"Step 1: Option 1 - Install Arduino IDE"),Object(i.b)("iframe",{width:"572",height:"320",src:"https://www.youtube.com/embed/0skX6HPSZnU",frameborder:"0",allow:"accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture",allowfullscreen:!0}),Object(i.b)("p",null,"Watch the video above to see how to install the Arduino IDE and get the library needed (it's all manual)."),Object(i.b)("p",null,"These are the steps followed in the video (Original Instructions by ",Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup"}),"Adafruit"),"):"),Object(i.b)("ul",null,Object(i.b)("li",{parentName:"ul"},Object(i.b)("p",{parentName:"li"},"Download and install the Arduino IDE (At least v1.8). Download it from ",Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://www.arduino.cc/en/Main/Software"}),"here"),". Do not install it from the App Store.")),Object(i.b)("li",{parentName:"ul"},Object(i.b)("p",{parentName:"li"},"Start the Arduino IDE")),Object(i.b)("li",{parentName:"ul"},Object(i.b)("p",{parentName:"li"},"Add ",Object(i.b)("inlineCode",{parentName:"p"},"https://www.adafruit.com/package_adafruit_index.json")," as an ",Object(i.b)("strong",{parentName:"p"},"Additional Board Manager URL")," (see image below)")),Object(i.b)("li",{parentName:"ul"},Object(i.b)("p",{parentName:"li"},"To add board Community nRF52 board support, start Arduino and open the Preferences window (",Object(i.b)("strong",{parentName:"p"},"File")," > ",Object(i.b)("strong",{parentName:"p"},"Preferences"),"). Now copy and paste the following 2 URLs into the 'Additional Boards Manager URLs' input field:"),Object(i.b)("p",{parentName:"li"},Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://www.adafruit.com/package_adafruit_index.json"}),"https://www.adafruit.com/package_adafruit_index.json"),"\n",Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://github.com/jpconstantineau/Community_nRF52_Arduino/releases/latest/download/package_jpconstantineau_boards_index.json"}),"https://github.com/jpconstantineau/Community_nRF52_Arduino/releases/latest/download/package_jpconstantineau_boards_index.json")))),Object(i.b)("p",null,Object(i.b)("img",Object(n.a)({parentName:"p"},{src:"https://cdn-learn.adafruit.com/assets/assets/000/040/294/large1024/microcontrollers_Screen_Shot_2017-03-19_at_22.16.49.png",alt:"Board Manager"}))),Object(i.b)("ul",null,Object(i.b)("li",{parentName:"ul"},"Open the ",Object(i.b)("strong",{parentName:"li"},"Boards Manager")," option from the ",Object(i.b)("strong",{parentName:"li"},"Tools -> Board")," menu and install ",Object(i.b)("inlineCode",{parentName:"li"},"Adafruit nRF52 by Adafruit")," (see image below)\n",Object(i.b)("img",Object(n.a)({parentName:"li"},{src:"https://cdn-learn.adafruit.com/assets/assets/000/039/907/large1024/microcontrollers_nRF52BSP.png?1488964156",alt:"Board Manager"})))),Object(i.b)("p",null,"It will take up to a few minutes to finish installing the cross-compiling toolchain and tools associated with this BSP."),Object(i.b)("p",null,Object(i.b)("strong",{parentName:"p"},"The delay during the installation stage shown in the image below is normal"),", please be patient and let the installation terminate normally:\n",Object(i.b)("img",Object(n.a)({parentName:"p"},{src:"https://cdn-learn.adafruit.com/assets/assets/000/040/938/large1024/microcontrollers_Screen_Shot_2017-04-19_at_20.23.20.png",alt:"Board Manager install progress"}))),Object(i.b)("p",null,'Once the Adafruit BSP is installed, click anywhere in the "Community Add on Adafruit nrf52 boards" box, and click "Install". This is a smaller installation and will happen much faster.'),Object(i.b)("p",null,Object(i.b)("img",Object(n.a)({parentName:"p"},{src:"https://github.com/jpconstantineau/Community_nRF52_Arduino/wiki/img/install_steps_board_manager.png",alt:"Community Add-on to Adafruit nRF52 Boards"}))),Object(i.b)("p",null,"Once the two BSP are installed, select the relevant board from the ",Object(i.b)("strong",{parentName:"p"},"Tools -> Board")," menu, which will update your system config to use the right compiler and settings for your nRF52 board:\n",Object(i.b)("img",Object(n.a)({parentName:"p"},{src:"https://cdn-learn.adafruit.com/assets/assets/000/094/506/large1024/microcontrollers_image.png?1598977463",alt:"Board Selection"}))),Object(i.b)("h3",{id:"step-1-option-2---install-arduino-cli-windows-script"},"Step 1: Option 2 - Install Arduino CLI (Windows script)"),Object(i.b)("iframe",{width:"572",height:"320",src:"https://www.youtube.com/embed/kJOem90845Y",frameborder:"0",allow:"accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture",allowfullscreen:!0}),Object(i.b)("p",null,"Watch the video above to see how to install the Arduino CLI and automatically get the library needed (it's in the script).",Object(i.b)("br",{parentName:"p"}),"\n","The script follows these steps:"),Object(i.b)("ul",null,Object(i.b)("li",{parentName:"ul"},"Download the arduino-cli using the steps outlined ",Object(i.b)("a",Object(n.a)({parentName:"li"},{href:"https://arduino.github.io/arduino-cli/latest/installation/"}),"here")),Object(i.b)("li",{parentName:"ul"},"Review the version installed ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli version")),Object(i.b)("li",{parentName:"ul"},"Add the configuration file ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli.yaml")," to the same folder where you have installed the executable binary for the arduino-cli.  This file contains the additional Boards Manager URLs. It's located in the utils folder of the firmware."),Object(i.b)("li",{parentName:"ul"},"Updates the index of cores from the added Boards Manager URLs: ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli core update-index")),Object(i.b)("li",{parentName:"ul"},"Upgrade all installed platforms to the latest version: ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli core upgrade")),Object(i.b)("li",{parentName:"ul"},"Make sure that the nRF52 Board Support Packages can be found: ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli core search nrf52")),Object(i.b)("li",{parentName:"ul"},"Install the Adafruit nRF52 Board Support Package by running: ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli core install adafruit:nrf52")),Object(i.b)("li",{parentName:"ul"},"Install the Community nRF52 Board Support Package by running: ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli core install community_nrf52:nrf52")),Object(i.b)("li",{parentName:"ul"},"Verify that the nRF52 boards were installed: ",Object(i.b)("inlineCode",{parentName:"li"},"arduino-cli board listall"))),Object(i.b)("h3",{id:"step-2-download-bluemicro_ble-firmware"},"Step 2: Download BlueMicro_BLE Firmware"),Object(i.b)("iframe",{width:"572",height:"320",src:"https://www.youtube.com/embed/eKDoVYfXWYQ",frameborder:"0",allow:"accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture",allowfullscreen:!0}),Object(i.b)("p",null,"To get a copy of the firmware, you have 3 options:"),Object(i.b)("ul",null,Object(i.b)("li",{parentName:"ul"},"Download the ",Object(i.b)("a",Object(n.a)({parentName:"li"},{href:"https://github.com/jpconstantineau/BlueMicro_BLE/archive/master.zip"}),"zip file")," of the master branch of the repository."),Object(i.b)("li",{parentName:"ul"},"Clone the repository localy  ",Object(i.b)("inlineCode",{parentName:"li"},"git clone https://github.com/jpconstantineau/BlueMicro_BLE.git")),Object(i.b)("li",{parentName:"ul"},"Fork the repo and clone locally.  If you want to save your changes and contribute back to the project, you will need to opt for this method.")),Object(i.b)("p",null,"Simplest is just to download the ",Object(i.b)("a",Object(n.a)({parentName:"p"},{href:"https://github.com/jpconstantineau/BlueMicro_BLE/archive/master.zip"}),"zip file"),".  In the video, I show the first 2 methods."),Object(i.b)("h3",{id:"step-3-edit-4-keyboard-files"},"Step 3: Edit 4 Keyboard Files"),Object(i.b)("iframe",{width:"572",height:"320",src:"https://www.youtube.com/embed/AjT15clmnmw",frameborder:"0",allow:"accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture",allowfullscreen:!0}),Object(i.b)("p",null,"Open the firmware in the IDE or your favorite editor, edit the following 4 files:"),Object(i.b)("ul",null,Object(i.b)("li",{parentName:"ul"},Object(i.b)("strong",{parentName:"li"},"hardware_config.h:")," for the GPIO definition of your keyboard. This file will vary depending on the controller you select."),Object(i.b)("li",{parentName:"ul"},Object(i.b)("strong",{parentName:"li"},"keyboard_config.h:")," for the BLE definition of your keyboard"),Object(i.b)("li",{parentName:"ul"},Object(i.b)("strong",{parentName:"li"},"keymap.cpp:")," for the keymaps definitions"),Object(i.b)("li",{parentName:"ul"},Object(i.b)("strong",{parentName:"li"},"keymap.h:")," to support the keymaps definitions")),Object(i.b)("p",null,"For more details on configuring your keyboard, look here..."),Object(i.b)("h3",{id:"step-4-compile-and-upload"},"Step 4: Compile and Upload"),Object(i.b)("iframe",{width:"572",height:"320",src:"https://www.youtube.com/embed/kJOem90845Y",frameborder:"0",allow:"accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture",allowfullscreen:!0}),Object(i.b)("p",null,"Video presents the Arduino-cli method."),Object(i.b)("p",null,"If you use the Arduino IDE, follow these steps:"),Object(i.b)("ul",null,Object(i.b)("li",{parentName:"ul"},'Select appropriate "Board" in the "Tools" menu'),Object(i.b)("li",{parentName:"ul"},"Compile"),Object(i.b)("li",{parentName:"ul"},"Connect your keyboard with USB cable"),Object(i.b)("li",{parentName:"ul"},'Select apropriate serial "Port" in the "Tools" menu'),Object(i.b)("li",{parentName:"ul"},"Upload - Depending on your hardware/firmware, you may need to double-press reset to put it in DFU mode"),Object(i.b)("li",{parentName:"ul"},'Go to your computer\'s Bluetooth connections and "add device"'),Object(i.b)("li",{parentName:"ul"},"You should be able to pair your keyboard")),Object(i.b)("div",{className:"footnotes"},Object(i.b)("hr",{parentName:"div"}),Object(i.b)("ol",{parentName:"div"},Object(i.b)("li",Object(n.a)({parentName:"ol"},{id:"fn-1"}),"nRF52840 Only.  With nRF52832, you still need software to flash.",Object(i.b)("a",Object(n.a)({parentName:"li"},{href:"#fnref-1",className:"footnote-backref"}),"\u21a9")))))}p.isMDXComponent=!0}}]);