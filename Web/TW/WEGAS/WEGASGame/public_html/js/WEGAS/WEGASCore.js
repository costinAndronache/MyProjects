/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var WEGAS = (function()
{
  
  var kMoveCommandName = "move";
  
  var EntityPrototype = 
  {
      id : undefined,
      presenter : undefined,
      positionComponent : undefined,
      init : function(id)
      {
          this.id = id;
          this.positionComponent = Object.create()
      }        
  };
    
   
   var CommandPrototype = 
   {
       name : undefined,
       parameters : undefined,
       entity : undefined,
       init : function(name, parameters, entity)
       {
           this.name = name;
           this.parameters = parameters;
           this.entity = entity;
       },
       
       toJson : function()
       {
          return JSON.stringify(this);
       }
   };
   
   var ComponentPrototype = 
   {
       entity : undefined,
       respondsToCommand : function(command)
       {
           return false;
       },
       executeCommand : function(command)
       {
           return false;
       },
       update : function(timePassedSinceLastCall)
       {
           console.log("WARNING, CALLING UPDATE ON A PROTOTYPE OR NOT OVERRIDEN METHOD!!");
       },
       
       commandCompletionFunction : undefined,
       
       initWithEntity : function(entity)
       {
           this.entity = entity;
       }
   };
   
   var PositionComponentPrototype = Object.create(CommandPrototype);
   PositionComponentPrototype.respondsToCommand = function(command)
   {
       if(command.name === kMoveCommandName)
       {
           return true;
       }
       
       return false;
   };
   PositionComponentPrototype.executeCommand = function(command)
   {
       if(command.name !== kMoveCommandName)
       {
           console.log("CALLING " + command.name + " ON POSITIONCOMPONENTPROTOTYPE");
       }
       
   };
   
   
    
    
    
})();
