
var AnimalPrototype = 
{
    numOfLegs : undefined,
    numOfEyes : undefined,
    init : function(legs, eyes)
    {
        this.numOfLegs = legs;
        this.numOfEyes = eyes;
    },
    roar : function()
    {
        return "nothing, i am just the protoype";
    }
};


var CatProtoype = Object.create(AnimalPrototype);
CatProtoype.roar = function(){return "meow";};


var myCat = Object.create(CatProtoype);

window.alert(myCat.roar());


