#define DATA 0b11000100    				     	    //Data to send   ||--------------------------------------------------------------||
#define SIZE 8			 		                    //Data size      || Able to change any data saize between 0-12 and any duty cycle|| 
#define BIT_TIME 10 								//clk duty cycle ||--------------------------------------------------------------||

boolean clkVal = false;          					//clk value
unsigned int dataToSend = DATA;  					//initialize data to send
unsigned int recievedData=0;   					    //initialize data to recieve

int index = 0;										//index of the sent data
int count = 0;									    //size of the recieved data
unsigned long current = 0;						    //keep the current time
bool flagIfRead = false;                            //flag to check if digit is already read

void setup() {
  	Serial.begin(9600);			 					//BAUD_RATE = 9600 
  	pinMode(5, OUTPUT);   		 					//initialize Tx - analog pin
  	pinMode(6,INPUT);				 				//initialize Rx - analog pin
  	pinMode(7, OUTPUT);			 					//initialize clkIn 
  	pinMode(8,INPUT);				 				//initialize clkOut  
}

void loop() {
    
    usart_tx();        			 				    //tranfer function
    usart_rx();         						    //reciever function
}

void usart_tx()
{ 
    if(index >= SIZE)                               //check that max digits sent is by SIZE
      index = 0;
  
    boolean leastSign = bitRead(dataToSend,index);  //lsb bit
    long timer = millis(); 				 			//time since turn on
    if (timer - current >= BIT_TIME)           	    //Timer
    {
  		clkVal = !clkVal;  				 			//flip the 1->0 and 0->1
        if(clkVal)                                  //if bit is 1 send data
        {        				 			
            digitalWrite(7, LOW);                   //do not send clk
            if(leastSign) 				 			//check lsb
				digitalWrite(5, HIGH);   			//if 1 so datapin 5 is 5 volt
          	else
              	digitalWrite(5, LOW);    			//if 0 so datapin 5 is 0 volt
            index++;                     			//index of the data
        }
      	else
          	digitalWrite(7, HIGH);                  //if bit is 0 send clk      
      current = millis();                           //current time                        
    }
}
void usart_rx()
{
  if (!digitalRead(8))							    //check if we are in "not read" mode
    flagIfRead = 0;									//if does turn flag to zero
  
  else if(digitalRead(8) && flagIfRead == 0)		//check if we are in "read" mode and flag is zero
  {
    flagIfRead = 1;									//turn flag to 1- we already read
 	bitWrite(recievedData, count, digitalRead(6));  //turn the digits into one number
	count++;										//count size of the nuber
  }
  if (count == SIZE)                                //check that all bits recieved
  {
   	Serial.println(recievedData,BIN);               //print the final data
   	count = 0;                                      //reset counter for new data
    recievedData = 0;                               //reset data for new data
  }
}
