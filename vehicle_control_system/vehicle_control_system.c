/*
 * vehicle_control_system.c
 *
 *  Created on: May 9, 2023
 *      Author: Ahmed Dwidar
 */
#include<stdio.h>

char traffic_light_color = 0;
float Room_Temp = 35;
float Engine_Temp = 50;
float engineTemp_return = 0;
float roomTemp_return = 0;
int speedOf_vehicle = 0;



typedef enum
{
	AC_off,AC_on
}Air_Condion_State;
typedef enum
{
	engineController_off,engineController_on
}engine_temp_controller;
typedef enum
{
	speed_0,speed_30 = 30,speed_100 = 100
}vehicle_speed;

typedef struct
{
	Air_Condion_State roomTemp_setting;
	engine_temp_controller engineTemp_setting;
	vehicle_speed speed;
} vehicle_states;

Air_Condion_State AC_State = AC_off;
engine_temp_controller  controller_state = engineController_off;


int vehicle_setups_speed(char traffic_light_color,vehicle_states *vehicle_states_ptr)
{
	if(traffic_light_color == 'G' || traffic_light_color =='g')
	{
		vehicle_states_ptr ->speed = speed_100;
	}
	else if(traffic_light_color == 'O' || traffic_light_color == 'o')
	{
		vehicle_states_ptr ->speed = speed_30;
	}
	else if(traffic_light_color == 'R' || traffic_light_color == 'r')
	{
		vehicle_states_ptr ->speed = speed_0;
	}
	return vehicle_states_ptr ->speed;
}
int vehicle_setups_room_temp(short Room_Temp,vehicle_states *vehicle_states_ptr)
{
	float roomTemp_setting = 35;
	if(Room_Temp < 10)
	{
		vehicle_states_ptr->roomTemp_setting = AC_on;
		AC_State = vehicle_states_ptr->roomTemp_setting;
		roomTemp_setting = 20;
	}
	else if(Room_Temp > 30)
	{
		vehicle_states_ptr->roomTemp_setting = AC_on;
		AC_State = vehicle_states_ptr->roomTemp_setting;
		roomTemp_setting = 20;
	}
	else
	{
		vehicle_states_ptr->roomTemp_setting = AC_off;
		AC_State = vehicle_states_ptr->roomTemp_setting;
	}

	return roomTemp_setting;
}
int vehicle_setups_engine_temp(short Engine_Temp,vehicle_states *vehicle_states_ptr)
{
	float engineTemp_setting = 70;

	if(Engine_Temp < 100)
		{
		engineTemp_setting = 125;
		vehicle_states_ptr->engineTemp_setting = engineController_on;
		controller_state = vehicle_states_ptr->engineTemp_setting;
		}
		else if(Engine_Temp > 150)
		{
			engineTemp_setting = 125;
			vehicle_states_ptr->engineTemp_setting = engineController_on;
			controller_state = vehicle_states_ptr->engineTemp_setting;
		}
		else
		{
			vehicle_states_ptr->engineTemp_setting = engineController_off;
			controller_state = vehicle_states_ptr->engineTemp_setting;
		}

	return engineTemp_setting;
}
void displayVehicleStates_speed(void)
{
	vehicle_states vehicle_status_configurations = {AC_off,engineController_off,speed_0};

	printf("b. enter the traffic light color\n");  fflush(stdout);
	scanf(" %c", &traffic_light_color);

	speedOf_vehicle = vehicle_setups_speed(traffic_light_color,&vehicle_status_configurations);

	printf("vehicle speed = %d KM/HR\n", speedOf_vehicle);
	printf("engine state is on\n");

	if(AC_State == AC_on)
	{
		printf("AC is on\n");
	}
	else
	{
		printf("AC is off\n");
	}
	if(controller_state == engineController_on)
	{
		printf("engine temperature controller is on\n");
	}
	else
	{
		printf("engine temperature controller is off\n");
	}

	printf("room temperature = %.2f c\n", Room_Temp);
	printf("engine temperature = %.2f c\n\n", Engine_Temp);
}
void displayVehicleStates_roomTemp(void)
{
	vehicle_states vehicle_status_configurations = {AC_off,engineController_off,speed_0};

	printf("b. enter the room temperature\n");  fflush(stdout);
	scanf("%f", &Room_Temp);

	roomTemp_return = vehicle_setups_room_temp(Room_Temp,&vehicle_status_configurations);

	/*Display the current vehicle state*/
	printf("vehicle speed = %d KM/HR\n", speedOf_vehicle);
	printf("engine state is on\n");
	if(AC_State == AC_on)
	{
		printf("AC is on\n");
	}
	else
	{
		printf("AC is off\n");
	}
	if(controller_state == engineController_on)
	{
		printf("engine temperature controller is on\n");
	}
	else
	{
		printf("engine temperature controller is off\n");
	}


	printf("room temperature = %.2f c\n", roomTemp_return);
	printf("engine temperature = %.2f c\n\n", Engine_Temp);

}
void displayVehicleStates_engineTemp(void)
{
	vehicle_states vehicle_status_configurations = {AC_off,engineController_off,speed_0};

	printf("b. enter the engine temperature\n");  fflush(stdout);
	scanf(" %f", &Engine_Temp);

	engineTemp_return = vehicle_setups_engine_temp(Engine_Temp,&vehicle_status_configurations);

	/*Display the current vehicle state*/
		printf("vehicle speed = %d KM/HR\n", speedOf_vehicle);
		printf("engine state is on\n");
		if(AC_State == AC_on)
		{
			printf("AC is on\n");
		}
		else
		{
			printf("AC is off\n");
		}
		if(controller_state == engineController_on)
		{
			printf("engine temperature controller is on\n");
		}
		else
		{
			printf("engine temperature controller is off\n");
		}

	if(speedOf_vehicle == 30)
	{
		/*room and engine temperatures if vehicle speed is 30km/hr (depending on traffic light color which states the vehicle speed)*/
		AC_State = AC_on;
		controller_state = engineController_on;
		roomTemp_return = (roomTemp_return*5/4) + 1;
		engineTemp_return = (engineTemp_return*5/4) + 1;
	}

	printf("room temperature = %.2f c\n", roomTemp_return);
	printf("engine temperature = %.2f c\n\n", engineTemp_return);

}
int main()
{
	char systemState, engineState;

	/*Ask the user the engine state he/she wants*/
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");  fflush(stdout);
	scanf(" %c",&systemState);

	if(systemState =='c')    /* print on screen that you quit the system*/
	{
		printf("Quit the system\n");
	}
	while(systemState != 'c')
	{
		switch(systemState)
		{
		case 'b':  /*Ask the user if he consider to quit the system */
			printf("Turn off the vehicle engine\n\n");

			printf("a. Turn on the vehicle engine\n");
			printf("b. Turn off the vehicle engine\n");
			printf("c. Quit the system\n");  fflush(stdout);
			scanf(" %c",&systemState);
			if(systemState =='c')  /* print on screen that you quit the system*/
			{
				printf("Quit the system\n");
			}
			break;
		case 'a':  /*Sensors set menu*/
			printf("a. Turn off the engine\n");
			printf("b. Set the traffic light color\n");
			printf("c. Set the room temperature\n");
			printf("d. Set the engine temperature\n");  fflush(stdout);
			scanf(" %c",&engineState);



			switch(engineState)
			{
			case 'a':  /*to make sure you can terminate the system after you apply your desired states */

				printf("a. Turn on the vehicle engine\n");
				printf("b. Turn off the vehicle engine\n");
				printf("c. Quit the system\n");  fflush(stdout);
				scanf(" %c",&systemState);

				break;
			case 'b':  /*setting traffic light color*/

				displayVehicleStates_speed();

				break;

			case 'c':  /*setting room temperature*/

				displayVehicleStates_roomTemp();

				break;

			case 'd':  /*setting engine temperature*/
				displayVehicleStates_engineTemp();

				break;

			}
	    }
	}



	return 0;
}
