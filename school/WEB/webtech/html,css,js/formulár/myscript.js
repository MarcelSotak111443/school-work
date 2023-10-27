


function modal(){ 
  if (controlAll() == true){

    var form = document.createElement("div");
    

    var grid = document.createElement("div");
    grid.setAttribute("style", "display: grid; grid-template-columns: 15% 85%; color:black");
    grid.setAttribute("class", "grid");



    var div = document.createElement("div");
    var div2 = document.createElement("div");

    grid.appendChild(div);
    grid.appendChild(div2);


    
    var name= document.createElement("p");
    var surname = document.createElement("p");
    var date= document.createElement("p");
    var age = document.createElement("p");
    var sex= document.createElement("p");
    var email = document.createElement("p");
    var phonenumber= document.createElement("p");
    var choosenSex = document.createElement("p");
    var scene= document.createElement("p");
    var role = document.createElement("p");
    var tools= document.createElement("p");
    var additionalTools = document.createElement("p");
    var service = document.createElement("p");
    var address = document.createElement("p");
    var nickname = document.createElement("p");
    var note = document.createElement("p");
    var time = document.createElement("p");
    var price = document.createElement("p");


    name.innerHTML = "Name";
    surname.innerHTML = "Surname";
    date.innerHTML = "Date Of Birth";
    age.innerHTML = "age";
    sex.innerHTML = "sex";
    email.innerHTML = "email";
    phonenumber.innerHTML = "phonenumber";
    choosenSex.innerHTML = "I choose";
    scene.innerHTML = "scene";
    role.innerHTML = "role";
    tools.innerHTML = "tools";
    additionalTools.innerHTML = "Aditional tools";
    service.innerHTML = "where";
    address.innerHTML ="my adress";
    nickname.innerHTML = "nickname";
    note.innerHTML = "note";
    time.innerHTML="time";
    price.innerHTML = "PRICE";


      div.appendChild(name);
      div.appendChild(surname);
      div.appendChild(date);
      div.appendChild(age);
      div.appendChild(sex);
      div.appendChild(email);
      div.appendChild(phonenumber);
      div.appendChild(choosenSex);
      div.appendChild(scene);
      div.appendChild(role);
      div.appendChild(tools);
     div.appendChild(additionalTools);
      div.appendChild(service);
      div.appendChild(address);
      div.appendChild(nickname);
      div.appendChild(note);
      div.appendChild(time)
      div.appendChild(price);




      
      var sum = 0;

      var name= document.createElement("p");
      name.innerHTML =  document.querySelector('input[id="name"]').value;


      var surname = document.createElement("p");
      surname.innerHTML =  document.querySelector('input[id="surname"]').value;

      var date= document.createElement("p");
      date.innerHTML =  document.querySelector('input[id="dateOfBirth"]').value;

      var age = document.createElement("p");
      age.innerHTML =  document.querySelector('input[id="age"]').value;

      var sex = document.createElement("p");
      sex.innerHTML = document.querySelector('input[name="sex"]:checked').value;

      var email = document.createElement("p");
       email.innerHTML =  document.querySelector('input[id="email"]').value;

      var phonenumber  = document.createElement("p");
      phonenumber.innerHTML = document.querySelector('input[id="phonePrefixList"]').value + document.querySelector('input[id="phone"]').value;

      var choosenSex  = document.createElement("p");
      choosenSex.innerHTML = document.querySelector('select[name="subjectus"]').value;

      var scene= document.createElement("p");
      scene.innerHTML = document.querySelector('select[name="topic"]').value;

      var role = document.createElement("p");

      role.innerHTML  = document.querySelector('select[name="chapter"]').value;

  // console.log(document.querySelector('input[id="email"]').value);
  
  // console.log(document.querySelector('input[id="phonePrefixList"]').value + document.querySelector('input[id="phone"]').value);
  // console.log(document.querySelector('select[name="subjectus"]').value);
  // console.log(document.querySelector('select[name="topic"]').value);
  // console.log(document.querySelector('select[name="chapter"]').value);


      var tools= document.createElement("p");

      var ele = document.getElementsByName('radio');
      for(i = 0; i < ele.length; i++) {
        if(ele[i].checked){
          tools.innerHTML += ele[i].value + " ";
           sum = sum + 10;
        }
       
      }
      if (tools.innerHTML === "") { tools.innerHTML = "none"}
      
      var where = document.createElement("p");
      where.innerHTML = document.querySelector('input[name="place"]:checked').value;
      
      if (where.innerHTML === "home") { sum = sum + 50}

      var service = document.createElement("p");
      service.innerHTML = document.querySelector('input[name="fillanswer"]').value;
      sum = sum + (countWords(service.innerHTML) * 10);
      console.log("second" + sum);
      if (service.innerHTML === "") {service.innerHTML = "no more tools"}


      var time = document.createElement("p");
      time.innerHTML = document.querySelector('select[name="time"]').value + "hour";
      sum = sum + parseInt(time.innerHTML) * 100;


       var address = document.createElement("p");
       address.innerHTML = document.querySelector('textarea[name="AreaHidden"]').value;
         if (address.innerHTML === "") {address.innerHTML = "no address user stays in club"}

       var nickname = document.createElement("p");
       nickname.innerHTML = document.querySelector('input[name="Nickname"]').value;
        if (nickname.innerHTML === "") {nickname.innerHTML = "no nickname"}

       var note = document.createElement("p");
       note.innerHTML  = document.querySelector('textarea[name="note"]').value;
       if (note.innerHTML === "") {note.innerHTML = "without note"}

var price = document.createElement("p");
console.log(sum);
price.innerHTML = sum  + "eur";
 
function countWords(s){
    s = s.replace(/(^\s*)|(\s*$)/gi,"");//exclude  start and end white-space
    s = s.replace(/[ ]{2,}/gi," ");//2 or more space to 1
    s = s.replace(/\n /,"\n"); // exclude newline with a start spacing
    return s.split(' ').filter(function(str){return str!="";}).length;
    //return s.split(' ').filter(String).length; - this can also be used
}


    
         div2.appendChild(name);
         div2.appendChild(surname);
         div2.appendChild(date);
         div2.appendChild(age);
         div2.appendChild(sex);
         div2.appendChild(email);
         div2.appendChild(phonenumber);
         div2.appendChild(choosenSex);
         div2.appendChild(scene);
         div2.appendChild(role);
         div2.appendChild(tools);
         div2.appendChild(service);
        div2.appendChild(where);
         div2.appendChild(address);
        div2.appendChild(nickname);
        div2.appendChild(note);
        div2.appendChild(time);
        div2.appendChild(price);
       
    var buttondiv = document.createElement("div");
    buttondiv.setAttribute("style","height:30px; text-align:center; text-align:center")


    var submit = document.createElement("div");
    submit.innerHTML = "Submit"
 
    submit.setAttribute("style","background-color: rgb(77,0,0); color: rgb(255, 214, 153); width:15%; height:100%; border-radius: 5px; cursor:pointer; margin:auto")
    
     buttondiv.appendChild(submit);
    
    form.appendChild(grid);
    form.appendChild(buttondiv);




var modalContent = document.createElement("div");
modalContent.classList.add("modalContent");
//modalContent.appendChild(closeBtn);

var text = "SUMMARY";
var paragraf= document.createElement("p");
paragraf.setAttribute("style", "text-align: center; background-color: rgb(77,0,0); color: rgb(255, 214, 153);");
paragraf.innerHTML = text;
modalContent.appendChild(paragraf);



var newButton = document.createElement("button");
var newContent = document.createTextNode("Cancel");
newButton.setAttribute("style", "text-align: center; background-color: rgb(77,0,0); color: rgb(255, 214, 153);");
  newButton.appendChild(newContent);
 //document.body.insertBefore(newButton, remove);
  

var upperLayer = document.getElementById("modal");
upperLayer.innerHTML = "";
upperLayer.appendChild(modalContent);
upperLayer.appendChild(form)
upperLayer.appendChild(newButton);
upperLayer.style.display = "block";


  newButton.addEventListener("click", createImage);
  submit.addEventListener("click", send);


function createImage(){
  upperLayer.style.display = "none";
  return false;

}
function send(){
   document.getElementById("form").submit();
}

}
else{
  
  return false;
}
}

  function CharCounter(object){
    console.log(object.value.toString().length);
    console.log(object.nextSibling.nextSibling.firstChild.nextSibling);


    object.nextSibling.nextSibling.firstChild.nextSibling.innerHTML = object.value.toString().length;
  }




  function controlAll(){

    const nodeList = document.querySelectorAll(".check");
    for (let i = 0; i < nodeList.length; i++) {

      if (nodeList[i].value === "") {
        nodeList[i].style.border = "2px solid red";
      }

    }
    for (let i = 0; i < nodeList.length; i++) {
      console.log(String(nodeList[i].computedStyleMap().get('border-color')));
      if (String(nodeList[i].computedStyleMap().get('border-color')) === "rgb(255, 0, 0)") {

        console.log(String(nodeList[i].computedStyleMap().get('border-color')));
        return false;
      }
    }
    return true;
    
  }



  function FieldCheck(object){
    var lessChar = "your answer must containt at least three symbols";
    var containNumber = "your answer contains number";
    var tooOld = "you are too old";
    var tooYoung = "you are too young";
    var unfilled = "empty field";
    var didntChooseFromList = "you didnt choose";
    var containLetter ="your answer contains character";
    var exactly9char ="you have to write exactly nine numbers";

    

    var check = new String();

    switch(object.name){
      case "name":
      case "surname":
      if (object.value.length < 3) { check += lessChar +"<br>"};
      if (/\d/.test(object.value)) {check += containNumber+"<br>"};


      

      break;

      case "age":
      changeDate(this);
        if (/[a-zA-Z]/.test(object.value)) {check += containLetter+"<br>"};
      if (object.value === "") {check += unfilled +"<br>"}
        if (true) {}
        case "date":

      var object2 = document.getElementById("dateOfBirth");

      var d = new Date(object2.value);
      console.log("wf"+    d);
      var currentDate = new Date();
      var currentYear = currentDate.getFullYear();
      if (!!d.valueOf()) {
        if (currentYear - d.getFullYear() > 120) { check += tooOld + "<br>"}
              console.log("wf"+  (currentYear - d.getFullYear() ) );
          if (currentYear - d.getFullYear() < 18) {check+= tooYoung + "<br>"}
        }
      if (check.length != 0){
        object2.style.border = "2px solid red";
        object.style.border = "2px solid red";
        object2.nextSibling.nextSibling.nextSibling.nextSibling.style.display = "block";
        object2.nextSibling.nextSibling.nextSibling.nextSibling.innerHTML = check;
      } 
      else
      {
        object2.style.border = "none";
         object2.nextSibling.nextSibling.nextSibling.nextSibling.style.display = "none";
        object2.nextSibling.nextSibling.nextSibling.nextSibling.innerHTML = check;

      }
      
     break;
     case "email":
     if (object.value === "") {check += unfilled +"<br>"};
     break;
     case "subjectus":
     case "topic":
     case "chapter":
     if (object.options[object.selectedIndex].text ==="Choose" ) {check += didntChooseFromList +"<br>"}
      break;
    case "fillanswer":
    case "AreaHidden":
      if (object.value.length < 3) { check += lessChar +"<br>"};
    case "Nickname":
    if (object.value === "") {
      check += unfilled +"<br>"
    }
    break;
    case "phone":
    if (object.value === "") {check += unfilled +"<br>"}
      if (/[a-zA-Z]/.test(object.value)) {check += containNumber+"<br>"};
    if (object.value.length != 9) {check += exactly9char+"<br>"};


    break;
    case "phonePrefix":
    if (object.value === "") {check += unfilled +"<br>"}
      if (/[a-zA-Z]/.test(object.value)) {check += containNumber+"<br>"};
    break;



  }

  if (check.length != 0) {
   
    
    object.style.border = "2px solid red";
    console.log(object.nextSibling.nextSibling.nextSibling.nextSibling);
    object.nextSibling.nextSibling.nextSibling.nextSibling.style.display = "block";
    object.nextSibling.nextSibling.nextSibling.nextSibling.innerHTML = check;
  }
  else{
    console.log( object.nextSibling.nextSibling.nextSibling.nextSibling);
   
   
    object.style.border = "none";
    document.getElementsByClassName("hints")[0].innerHTML = "";
    object.nextSibling.nextSibling.nextSibling.nextSibling.style.display = "none";
    object.nextSibling.nextSibling.nextSibling.nextSibling.innerHTML = check;


  }
  check = "";

}
function FillAdvise(object){
	var adviseText = "";
	var lenghtOftext = "your answer must containt at least three symbols";
	var noNumber = " your answer contains number";
	var textWithStarNumber = "your answer cannot start with number";
	var tooOld = "you have to be younger than 125 years";
	var tooYoung = "you have to be at least 18 years old";
  var emailInfo = "email must containt at least three letters at the begining followed by @ folowed by at least three letters and ended with at least two letters";
  var justchoose ="you have to choose";
  var onlyNumbers = "your answer can contin only numbers";
  var exactly9char ="you answer has to be nine numbers long"

  
  switch(object.name){
    case "name":
    case "surname":
    adviseText += lenghtOftext +"<br>";
    adviseText += noNumber+"<br>";
    adviseText += textWithStarNumber+"<br>";
    break;
    case "date":
    case "age":
    adviseText += tooOld +"<br>";
    adviseText += tooYoung+"<br>";
    break;
    case "email":
    adviseText += emailInfo+"<br>";
    break;
    case "subjectus":
    case "topic":
    case "chapter":
    adviseText += justchoose+"<br>";
    adviseText += onlyNumbers+"<br>";
    break;
    case "phone":
    adviseText += onlyNumbers+"<br>";
    adviseText += exactly9char+"<br>";

    break;
    case "phonePrefix":
    adviseText += justchoose+"<br>";
    adviseText += onlyNumbers+"<br>";
    break;
    case "fillanswer":
    case "AreaHidden":
    case "Nickname":
    adviseText += lenghtOftext +"<br>";
    break;


  }
  document.getElementsByClassName("hints")[0].innerHTML = adviseText;
  adviseText = "";
}

//first
function setAge() {
  var date = document.getElementById( "dateOfBirth" );
  var dateValue = date.value;
  var age = document.getElementById( "age" );
  var currentYear = new Date().getFullYear();
  var yearDifference;

  var d = new Date( dateValue );
  if ( !!d.valueOf() ) 
  {
   year = d.getFullYear();
   yearDifference = currentYear - year;
   age.value = yearDifference;
 } 
}
//second

function changeDate(object){

	var dateFull = document.getElementById( "dateOfBirth" );
	var date = dateFull.value;
  var age = document.getElementById( "age" ).value;

  var today = new Date();
  var thisYear = today.getFullYear();
    // document.write(thisYear);

    var d = new Date(date);
    if ( !!d.valueOf() ) {
      var day = d.getDate();
      if (day <= 9) { day = '0'+day;}
      var month = d.getMonth()+1;
      if (month <= 9) { month = '0'+month;}
      var year = thisYear - age
      var d = `${year}-${month}-${day}`;
      console.log(thisYear - age);
      console.log(d);
      dateFull.value = d;
      return;
    }
  }
//third
var subjectObject = {
  "Woman": {
    "normal": ["fat","slim"],
    "prison": ["prisoner","cop"],
    "school": ["teacher", "student"],
    "hospital": ["doctor", "pacient"]    
  },
  "Man": {
    "repair shop": ["plumber", "mechanic",],
    "policeman": ["hot", "superHot", "sixpack"]
  }
}
window.onload = function() {
  var subjectSel = document.getElementById("subject");
  var topicSel = document.getElementById("topic");
  var chapterSel = document.getElementById("chapter");
  for (var x in subjectObject) {

  	subjectSel.options[subjectSel.options.length] = new Option(x, x);

  }
  subjectSel.onchange = function() {
    chapterSel.length = 1;
    topicSel.length = 1;
    //display correct values
    for (var y in subjectObject[this.value]) {
      topicSel.options[topicSel.options.length] = new Option(y, y);
    }
  }
  topicSel.onchange = function() {
  	chapterSel.length = 1;
    var z = subjectObject[subjectSel.value][this.value];
    for (var i = 0; i < z.length; i++) {
      chapterSel.options[chapterSel.options.length] = new Option(z[i], z[i]);
    }
  }
}
//fourth
function displayHiddenDivFunkcion(){
	
  if (document.getElementById( "home" ).checked){
   document.getElementsByClassName("hiddenPart")[0].style.display = "block";
 }
 if (document.getElementById( "atClub" ).checked){
   document.getElementsByClassName("hiddenPart")[0].style.display = "none";

 }
}
//fifth
function showHiddenAnswer(){
	if  (document.getElementById( "ownAnswer" ).checked){
		document.getElementsByClassName("hiddenTextField")[0].style.display = "block";

  }
  else{
   document.getElementsByClassName("hiddenTextField")[0].style.display = "none";
 }
}
//6
function reavealNameField(){
	document.getElementsByClassName( "hiddenTextFieldForName" )[0].style.display = "block";
}
