console.log("Loading...");
customElements.define("custom-element", CustomElement);





document.addEventListener("update-amplitude" ,function(event){
    console.log(multipplyier );
    console.log(event.detail.value);
    multipplyier = event.detail.value;
  
});

