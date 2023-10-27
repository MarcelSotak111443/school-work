var minimum = 0;
var maximum = 0;


class CustomElement extends HTMLElement{
    constructor(){
    super();

    this.attachShadow({mode:"open"});

    const wrapper = document.createElement("div");
    wrapper.setAttribute("class", "wrapper");

    
    const amplitude = wrapper.appendChild(document.createElement("input"));
    amplitude.setAttribute("type", "range");
    amplitude.setAttribute("id" , "amplitude1");

    let minimum = this.hasAttribute("min-val")? this.getAttribute("min-val") : 0;
    let maximum = this.hasAttribute("max-val")? this.getAttribute("max-val") : 9;

    amplitude.setAttribute("value", minimum);
    amplitude.setAttribute("min", minimum);
    amplitude.setAttribute("max", maximum);
    
    amplitude.setAttribute("oninput" , "this.nextElementSibling.value = this.value");
        
        const div = wrapper.appendChild(document.createElement("output"));
        div.innerHTML = minimum;

    const Textinput = wrapper.appendChild(document.createElement("input"));
    Textinput.setAttribute("type","number");
    Textinput.setAttribute("id","text-input");
    Textinput.setAttribute("class","textInput");
    


    Textinput.innerHTML = this.hasAttribute("text") ? this.getAttribute("text") : "Tlacidlo";


   

    style.textContent = ' ' +
    '.wrapper{margin:auto}'+
    '.wrapper{width:200px}'+
    '.textInput{width: 192px;}'+
    '#amplitude1{width: 200px;}'+
    'output{margin-left:45%}';






    this.shadowRoot.append(wrapper);
    this.shadowRoot.append(style);

     this.clickEventFunc = (event) =>{
        console.log(Textinput.value);
            console.log(maximum);

           
        if(parseInt(Textinput.value) > parseInt(maximum)){
            Textinput.value = maximum;
        }
        if(parseInt(Textinput.value) < parseInt(minimum)){
            console.log(Textinput.value);
            console.log(minimum);
            Textinput.value = minimum;
        }
        amplitude.value = Textinput.value;
        div.innerHTML = Textinput.value;
    
         const customEvent = new CustomEvent('update-amplitude', {
             bubbles: true,
             composed: true,
             detail: {value: event.target.value}
            
         });
         this.dispatchEvent(customEvent);
     }
     this.shadowRoot.querySelector('#text-input').addEventListener("input", this.clickEventFunc);

    this.updateAmpFunc = (event) =>{
        console.log("wtf");
        Textinput.value = amplitude.value;
        const customEvent = new CustomEvent('update-amplitude', {
            bubbles: true,
            composed: true,
            detail: {value: event.target.value}
        });
        this.dispatchEvent(customEvent);
    }
    this.shadowRoot.querySelector('#amplitude1').addEventListener("change", this.updateAmpFunc);





    }
}