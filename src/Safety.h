/**
 * file that contains the class with the logic needed for safe operations in the
 * operation space.
 * it also includes the procedure needed for changing from a position to another
 * 
 * */

class SafetyController{
    
    public:

    /**
     * function that is used just one time to set the safe positions. 
     * the ground one, the one that is used to connect the pins and the 
     * switches, the one that prevents inclination and rotation
     * 
     * */
    void startup(){
        ground.setZ(Z_GROUND);
        ground.setRotation(0);
        ground.setInclination(0);

        
        connectPins.setZ(Z_PINS);
        connectPins.setRotation(0);
        connectPins.setInclination(0);

        
        switches.setZ(Z_GROUND);
        switches.setRotation(180);
        switches.setInclination(0);

        //ultrasonicSensor.setup();
    }

    /**
     * Function that recieves a desired position and check if is possible to be reached
     * it checkes the position but also the sensors
     * INPUT: desired positin
     * OUTPUT: a boolean that allows or blocks the movement of the platform
     * */
    boolean isSafe(Position desired){
        if (isNewPallet(desired)){
            return true; //means that i have to ignore SOME safety feature
        }
        
        //then i check if i can reach that position
        boolean isOk = isReachable(desired);
        
        //then it checks if the area around is safe
        if(isOk){
           //isOk = isSafeToMove();
            isOk = true;
        }
        else{
            //means that i cannot move the platform
            //due to reachability constraints
            ledBlink();
        }


        return isOk;
        //return true;
    }

    
    /**
     * Function that turns on or off the led
     * INPUT: delta is the difference from the desired and current position, inlcuding the tollerance
     * */

    void moving(int delta){
      if (delta == 0) 
      {
        //means that the platform is not mooving
        setLed(true);
      }
      else 
      {
        setLed(false);
      }
      
    }




    private:
        boolean newPallet = true;
        boolean ignorePins = false;
        boolean contactSwitch = false;
        boolean areaFree = false;
        boolean lights = true; //true means grean and false means red light
        Position ground, connectPins, switches;

        UltrasonicSensor ultrasonicSensor;

        /**
         * Function that controls the LED on and off behavior
         * INPUT: is the new value of the leds if the movement is accouring
         *          or is not safe to move
         * */
        void setLed(boolean toSetLight){
            lights = toSetLight;
            if (lights)
            {//if true means green
                digitalWrite(LED_PIN,HIGH);
                digitalWrite(LED_BUILTIN,HIGH);
            }
            else{
                digitalWrite(LED_PIN,LOW);
                digitalWrite(LED_BUILTIN,LOW);
            }
            
        }

        /**
         * Funcition that make the led blinks
         * */        
        void ledBlink(){
            setLed(false);
            delay(LED_BLINK);
            setLed(true);
            delay(LED_BLINK);
            setLed(false);
        }

        /**
         * it check if the position send won't violate any safety standards
         * INPUT: the desired position
         * OUTPUT: a boolean that tells the controller if the position is reachable
         * */
        
        boolean isReachable(Position desired){
            
            boolean zOutOfRange = desired.getZ() > Z_MAXLENGHT || desired.getZ() < Z_MINLENGHT ;
            if(zOutOfRange){
                Serial.println("Z out of reach");
                return false;
            }

            boolean inclineOutOfRange = desired.getInclination() > INCLINATION_MAX ||desired.getInclination() < INCLINATION_MIN ;
            if (inclineOutOfRange)
            {
                Serial.println("Inclination out of reach");
                return false;
            }

            //the rotation cannot be out of range due to the fact that the encord has an infinite type of rotation

            boolean onlyZ = desired.getRotation()> ROT_MIN || desired.getInclination() > INCLINATION_MIN;
            if (desired.getZ() > Z_NO_INCLINATION && onlyZ ) //means that i cannot incline and i want to
            {
                Serial.println("No inclination/rotation at this Z");
                return false;
            }

            return true;
        }

        /**
         * Funciton that checks if i'm working with a new pallet and in case
         * ignoring some of the safety feature
         * 
         * INPUT: is the desired position. if it is the first position that is used 
         *          to connect the pallet to the platform, it's safe to ignore some pins
         * OUTPUT: is a boolean value that say if the platform can ingnore some safety 
         *         functions
         * 
         * */
        boolean isNewPallet(Position desired){
            //means that i have a new pallet
            if(isSamePosition(desired,ground) && newPallet == true){
                newPallet = false;
                return true;
            }

            //means that i've completed the operations and coming back down to the gound
            if(isSamePosition(desired,ground) && newPallet == false){
                newPallet = true;
                return false;
            }

            //means that's not a new pallet
            if(newPallet == false){
                return false;
            }
            return false;
        }

        /**
         * Function that check if the two positions are the same
         * INPUT: the desired position and the one that needs to be checked
         * OUTPUT: a boolean value that says if the two position are the same
         * */
        boolean isSamePosition(Position desired, Position checked){
            if(desired.getInclination() == checked.getInclination())
            {
                if (desired.getRotation() == checked.getRotation())
                {
                    if (desired.getZ() == checked.getZ())
                    {
                        return true;
                    }
                    
                    
                }
            }
            else
            {
                return false;
            }
            return false;
        }

        /**
         * Function that compares the minimum distance emasured to the minimum required for safety
         * It uses the ultrasonic sensors
         * */
        boolean isSafeToMove(){
             //unsigned int distance = ultrasonicSensor.getSmallestDistance();
            
            if (ultrasonicSensor.getSmallestDistance() > MINIMUM_DISTANCE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
};