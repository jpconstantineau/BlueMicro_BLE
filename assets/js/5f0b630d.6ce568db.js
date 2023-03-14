"use strict";(self.webpackChunkdocumentation=self.webpackChunkdocumentation||[]).push([[4269],{3905:function(e,t,n){n.d(t,{Zo:function(){return u},kt:function(){return m}});var a=n(7294);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function l(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function o(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?l(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):l(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function i(e,t){if(null==e)return{};var n,a,r=function(e,t){if(null==e)return{};var n,a,r={},l=Object.keys(e);for(a=0;a<l.length;a++)n=l[a],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var l=Object.getOwnPropertySymbols(e);for(a=0;a<l.length;a++)n=l[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var d=a.createContext({}),c=function(e){var t=a.useContext(d),n=t;return e&&(n="function"==typeof e?e(t):o(o({},t),e)),n},u=function(e){var t=c(e.components);return a.createElement(d.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},s=a.forwardRef((function(e,t){var n=e.components,r=e.mdxType,l=e.originalType,d=e.parentName,u=i(e,["components","mdxType","originalType","parentName"]),s=c(n),m=r,k=s["".concat(d,".").concat(m)]||s[m]||p[m]||l;return n?a.createElement(k,o(o({ref:t},u),{},{components:n})):a.createElement(k,o({ref:t},u))}));function m(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var l=n.length,o=new Array(l);o[0]=s;var i={};for(var d in t)hasOwnProperty.call(t,d)&&(i[d]=t[d]);i.originalType=e,i.mdxType="string"==typeof e?e:r,o[1]=i;for(var c=2;c<l;c++)o[c]=n[c];return a.createElement.apply(null,o)}return a.createElement.apply(null,n)}s.displayName="MDXCreateElement"},3035:function(e,t,n){n.r(t),n.d(t,{contentTitle:function(){return d},default:function(){return s},frontMatter:function(){return i},metadata:function(){return c},toc:function(){return u}});var a=n(7462),r=n(3366),l=(n(7294),n(3905)),o=["components"],i={id:"keycodes_firmware",title:"Firmware-only Keycodes",slug:"/keycodes_firmware"},d=void 0,c={unversionedId:"keycodes/keycodes_firmware",id:"keycodes/keycodes_firmware",title:"Firmware-only Keycodes",description:"Firmware only keycodes are keycodes that modify the behavior of the keyboard firmware and are processed to send something different.",source:"@site/docs/keycodes/firmware.md",sourceDirName:"keycodes",slug:"/keycodes_firmware",permalink:"/docs/keycodes_firmware",editUrl:"https://github.com/jpconstantineau/BlueMicro_BLE/tree/documentation-docusaurus/documentation/docs/keycodes/firmware.md",tags:[],version:"current",frontMatter:{id:"keycodes_firmware",title:"Firmware-only Keycodes",slug:"/keycodes_firmware"},sidebar:"someSidebar",previous:{title:"Toggles and One-Shot",permalink:"/docs/keycodes/keycodes_modifiers"},next:{title:"Hardware-specific Keycodes",permalink:"/docs/keycodes_hardware"}},u=[{value:"Layers",id:"layers",children:[],level:3}],p={toc:u};function s(e){var t=e.components,n=(0,r.Z)(e,o);return(0,l.kt)("wrapper",(0,a.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,l.kt)("p",null,"Firmware only keycodes are keycodes that modify the behavior of the keyboard firmware and are processed to send something different. "),(0,l.kt)("h3",{id:"layers"},"Layers"),(0,l.kt)("p",null,"These keycodes are used by the firmware to switch from one layer to another."),(0,l.kt)("table",null,(0,l.kt)("thead",{parentName:"table"},(0,l.kt)("tr",{parentName:"thead"},(0,l.kt)("th",{parentName:"tr",align:null},"Usage ID (HEX)"),(0,l.kt)("th",{parentName:"tr",align:null},"Usage Name"),(0,l.kt)("th",{parentName:"tr",align:null},"Keycode Identifiers"))),(0,l.kt)("tbody",{parentName:"table"},(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF0"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 0 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_0")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF1"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 1 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_1")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF2"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 2 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_2")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF3"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 3 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_3")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF4"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 4 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_4")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF5"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 0 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_5")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF6"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 1 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_6")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF7"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 2 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_7")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF8"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 3 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_8")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xF9"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 4 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_9")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xFA"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 4 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_A")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xFB"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 0 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_B")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xFC"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 1 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_C")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xFD"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 2 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_D")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xFE"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 3 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_E")),(0,l.kt)("tr",{parentName:"tbody"},(0,l.kt)("td",{parentName:"tr",align:null},"0xFF"),(0,l.kt)("td",{parentName:"tr",align:null},"Access Layer 4 (default)"),(0,l.kt)("td",{parentName:"tr",align:null},"LAYER_F")))),(0,l.kt)("p",null,"If you want to activate a layer by pressing a combination of two other layer keycodes, you can use the function ",(0,l.kt)("inlineCode",{parentName:"p"},"process_user_layers")," to define the behavior you want."),(0,l.kt)("p",null,"You will need to add the following two lines to your ",(0,l.kt)("inlineCode",{parentName:"p"},"keymap.h")),(0,l.kt)("pre",null,(0,l.kt)("code",{parentName:"pre",className:"language-c++"},"#define USER_LAYER_FUNCTION   0 \nvoid process_user_layers(uint16_t layermask);\n")),(0,l.kt)("p",null,"You will also need to define which two layer activate the 3rd one. This is done by adding a few lines in ",(0,l.kt)("inlineCode",{parentName:"p"},"keymap.cpp")),(0,l.kt)("pre",null,(0,l.kt)("code",{parentName:"pre",className:"language-c++"},"void process_user_layers(uint16_t layermask)\n{\n    KeyScanner::process_for_tri_layers(_L1, _L2, _L3);\n}\n")),(0,l.kt)("p",null,"In the example above, both LAYER_1 and LAYER_2 need to be pressed for LAYER_3 to be activated.\nNote that ",(0,l.kt)("inlineCode",{parentName:"p"},"_L1"),", ",(0,l.kt)("inlineCode",{parentName:"p"},"_L2")," and ",(0,l.kt)("inlineCode",{parentName:"p"},"_L3")," are not keycodes."),(0,l.kt)("p",null,"If combinations with more layers are needed, you can add them in that function."),(0,l.kt)("p",null,"Page is still a work in progress.  Refer to ",(0,l.kt)("inlineCode",{parentName:"p"},"hid_keycodes.h")," and ",(0,l.kt)("inlineCode",{parentName:"p"},"advanced_keycodes.h")," for a detailed list of keycodes."))}s.isMDXComponent=!0}}]);