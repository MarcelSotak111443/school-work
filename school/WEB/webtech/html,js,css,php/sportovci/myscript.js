  


console.log("ehja");

  function FieldCheck(object){
     
    var lessChar = "your answer must containt at least two symbols";
    var containNumber = "your answer contains number";
    var notsame = "not the same password";
    var wrongFormat = "format should me yyyy-mm-dd";
    var onlynumbers = "only numbers";
     var wrongEmailFormat = "wrongFormat";
 
 

    

    var check = new String();

    switch(object.name){
    
      case "name":
    
     
      if (object.value.length < 2) { check += lessChar +"<br>"};
      if (/\d/.test(object.value)) {check += containNumber+"<br>"};
      break;

      case "surname":

      case "birth_country":
      case "birth_place":
      case "city":
  if (object.value.length < 2 && object.value.length != 0) { check += lessChar +"<br>"};
      //if (/\d/.test(object.value)) {check += containNumber+"<br>"};

      break;
    case "email":
    var emailPattern = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
    if(!emailPattern.test(object.value)){
      console.log(emailPattern.test(email))  ;
            check += wrongEmailFormat+"<br>";
    }
      
break;
    

    case "placing":
      if (! !isNaN(parseFloat(object.value)) && isFinite(object.value)) {
        check += onlynumbers+"<br>";
        console.log("nigger");
      }
    break;
    case "birth_day":
      const regex = /^\d{4}-\d{2}-\d{2}$/;
      if (!regex.test(object.value) && object.value != "") {

    check += wrongFormat +"<br>";
    if (! !isNaN(parseFloat(object.value)) && isFinite(input.value)) {
        check += onlynumbers+"<br>";
      }
      } 
    break;
    case "psw":
    case "psw-repeat":
    var passwordInput = document.getElementsByName("psw")[0];
    var passwordInputSecond = document.getElementsByName("psw-repeat")[0];

    if (passwordInput.value != passwordInputSecond.value) {
      check += notsame+"<br>";
       passwordInput.style.border = "2px solid red";
       passwordInput.nextSibling.nextSibling.innerHTML = check;
       passwordInputSecond.style.border = "2px solid red";
       passwordInputSecond.nextSibling.nextSibling.innerHTML = check;
    }else{
       passwordInput.style.border = "1px solid black";
       passwordInput.nextSibling.nextSibling.innerHTML = ' ';
       passwordInputSecond.style.border = "1px solid black";
       passwordInputSecond.nextSibling.nextSibling.innerHTML = ' ';
    }

    
    break;
     

  }
  

   if (check.length != 0){
        object.style.border = "2px solid red";
      
     console.log(object.nextSibling.nextSibling);
        object.nextSibling.nextSibling.innerHTML = check;
      } else{
        object.style.border = "1px solid black";
      
   
        object.nextSibling.nextSibling.innerHTML = '';
      }


     function validateForm() {
      console.log("working");
    const nodeList = document.querySelectorAll(".check");
    for (let i = 0; i < nodeList.length; i++) {
      if (nodeList[i].value === "") {
        nodeList[i].style.border = "2px solid red";
      }
    }
    for (let i = 0; i < nodeList.length; i++) {
      if (String(nodeList[i].computedStyleMap().get('border-color')) === "rgb(255, 0, 0)") {
        console.log(String(nodeList[i].computedStyleMap().get('border-color')));
        return false;
      }
    }
    return true;
  }
     
}