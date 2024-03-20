## Still under development
# Car Parking Reservation System

This project is a Car Parking Reservation System implemented in C. It's a console-based application that simulates the parking process of a parking lot.

## Features

1. **Authentication**: The system is secured with a password. Only users who know the password can access the system. The default password is 'abcd1234'.

2. **Arrival of a Car**: The system captures the details of a car upon arrival. The user is prompted to enter the driver's name, car number, hours of stay, and time slot. If the hours of stay are less than 8, the car is allowed to park and the details are stored in a binary file named 'parkingprojectfile'.

3. **Record Management**: The system provides a feature to view the records of all parked cars. It reads the details from the 'parkingprojectfile' and displays them.

4. **Parking Cost Calculation**: The system calculates the parking cost based on the hours of stay. It has a different pricing model for VIP customers and regular customers.

5. **Departure of a Car**: The system handles the departure of a car. The user is prompted to enter the car number of the departing car and the system deletes the corresponding record from the 'parkingprojectfile'.

6. **Program Termination**: The user can choose to exit the program. Upon choosing this option, a thank you message is displayed and the program terminates.

## Usage

To use this system, compile the `parkingproject.c` file and run the resulting executable. Follow the prompts in the console to interact with the system.

## Contributing

Contributions are welcome! For major changes, please open an issue first to discuss what you would like to change. Please make sure to update tests as appropriate.

## License

This project is licensed under the [MIT](https://choosealicense.com/licenses/mit/) license.
