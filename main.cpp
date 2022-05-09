//ASSIGNMENT 1
//ANDREW CHEBLI
//ID:40125859




#include <iostream>

using namespace std;

class Date{
    private:
        int day;
        int month;
        int year;

    public:
        Date(int day, int month, int year){
            this->day = day;
            this->month = month;
            this-> year = year;
        }
        void setDay(int day){
            this->day = day;
        }
        void setMonth(int month){
            this->month = month;
        }
        void setYear(int year){
            this->year = year;
        }
        int getDay(){
            return day;
        }
        int getMonth(){
            return month;
        }
        int getYear(){
            return year;
        }
};

class information{
    private:
        string first_name;
        string last_name;
        Date *birth_date; 
    public:
        information(){
            first_name = "";
            last_name ="";
            birth_date = nullptr;
        }
        information(string firstName, string lastName, Date *d){
            first_name = firstName;
            last_name = lastName;
            birth_date = d;
        }
        void setFirst(string firstName){
            first_name = firstName;
        }
        string getFirst(){
            return first_name;
        }
        void setLast(string lastName){
            first_name = lastName;
        }
        void printInfo(){
            cout << "First name : " << first_name << "  last name: " << last_name <<endl;
           

            cout <<"Birth date: DD/MM/YY " << birth_date->getDay() << "/" << birth_date->getMonth() << "/" << birth_date->getYear() << endl;
        }
        bool empty(){ // check if there is no name available--> no person available
            if(getFirst() == "" ){
                return true;
            }else{
                return false;
            }
        }

};

class Guests{
    private:
        static const size_t size = 4;
        Date *checkIn;
        Date *checkOut;
        information *info ;
        int room_number;


    public:
       
        Guests(Date checkIn, Date checkOut, int roomNumber){
            info = new information[size];
            this->checkIn = &checkIn;
            this->checkOut = &checkOut;
            this->room_number = roomNumber;
        }

        void addInfo(information info, int guest){ // add information to info array
            this->info[guest] = info;
        }
        void printGuests(int i){
            this->info[i].printInfo();
        }
        void printMyInfo(){ // to print without specifying the number of guests beforehand
            
            int i =0;
            
            while(i < size && !info[i].empty()){
                
                this->info[i].printInfo();
                i++;
            }
        }
        ~Guests(){
            
        }

};
class Guests_Res_Request{
    private:
        Guests *guest;
        static int counter;
        int id;
        int numberOfNights;

    public:
        Guests_Res_Request(){
            id =0;
            numberOfNights =0;
        }
        Guests_Res_Request(Date checki, Date checko, Guests g){
            id = counter;
            counter++;
            numberOfNights = checko.getDay() - checki.getDay();
            guest = &g;
        }
        int getId(){
            return id;
        }
        int getCounter(){
            return counter;
        }
        void printRequest(){ // to print the reservation request.
            cout << "your reservation information is: " <<endl;
            guest->printMyInfo();
        }
};
int Guests_Res_Request::counter =1;

class Reservation_Manager{
    private:
        int max_no_of_nights = 7;
        static int no_of_rooms;
        Guests_Res_Request *arr;
        int **table ;


    public:
        Reservation_Manager(){ // create the object for the manager
            arr = new Guests_Res_Request[10];//assumed maximum number of clients is 10 but the exercice said 1 room only is reserved
            table = new int*[max_no_of_nights];
            for(int i =0; i < max_no_of_nights; i++){
                table[i] = new int[20];
            }
            for(int row = 0; row < max_no_of_nights; row++){
                for(int col = 0; col < no_of_rooms; col++){
                    table[row][col] = 0;
                }
            }
        }
        void addRequest(Guests_Res_Request reservation,int i){ // add the request to the array of guest reservation request
            arr[i] = reservation; 
        }
        
        void printTable(){ // print a table
            cout << "       | ";
            for(int i =1; i < no_of_rooms/2; i++ ){
                cout  <<i <<  " | ";
                
            }
            for(int i =no_of_rooms/2 ; i <= no_of_rooms; i++){
                cout << i << "| ";
            }
            cout << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;

            for(int row = 0; row < max_no_of_nights; row++){
                cout << "march " << row+1<<"| ";
                for(int col = 0; col < no_of_rooms; col++){
                    cout << table[row][col] << " | ";
                }
                cout << endl;
                cout << "----------------------------------------------------------------------------------------" << endl;
            }
            
        }
        void editTable(Date in, Date out, int room, Guests_Res_Request g){ // to edit the table with the new id added
            for (int i =in.getDay(); i <= out.getDay(); i++){
                table[i-1][room-1] = g.getId();
            }

        }
        void cancelReservation(int id){ // cancel the reservation
            for(int i = 0; i <max_no_of_nights;i++ ){
                for(int j = 0; j < no_of_rooms; j++){
                    if(table[i][j] == id){
                        table[i][j] = 0;
                    }
                }
            }
            arr[id -1] = Guests_Res_Request();
        }
        bool Gusts_Res_Request(Date checkIn, Date checkOut, int room){ // check if room is taken or not
            int i =checkIn.getDay();
            bool temp ;
            while( i < checkOut.getDay()){
                if(table[i-1][room-1] == 0){
                    temp = true;
                    i++;
                    continue;
                    
                }else{
                    
                    temp = false;
                    cout << "room not available";
                    break;
                }
                i++;
            }
            return temp;

        }
        void findId(int id){ // print the information after getting the id
            cout << "reservation info for id: " << id << endl;
            for(int i =0; i < 10; i++){
                if(arr[i].getId() == id){
                    arr[i].printRequest();
                    break;
                }
            }
        }

};
int Reservation_Manager::no_of_rooms =20;






int main(){
    Reservation_Manager manager; // create a manager object to store the id's in the schedule table
    int temp = 1;
    int client =0;
    while (true){
    cout <<"welcome to hotel CPlusPlus, please choose from the following menu:" << endl;
    cout << "[1] make a reservation" << endl;
    cout << "[2] cancel a reservation" << endl;
    cout << "[3] check reservation information" << endl;
    cout << "[4] leave the menu" << endl;
    int menu;
    int roomNumber;
    cin >> menu;
    
    if(menu == 4){
        break;
    }else if(menu == 1){

    
    int day, month, year;
    cout <<"when is your checkin date? DD/MM/YY" <<endl;
    cin >> day >> month >> year;
    Date checkin(day, month, year);
    cout << "when is your check out date ? DD/MM/YY" << endl;
    cin >> day >> month >> year;
    Date checkout(day, month, year);
    
    
    cout << "how many people are staying?" <<endl;
    int people;
    cin >> people;
    Guests stay(checkin, checkout, 19);
    string first;
    string last;
    
    Date * birthday;
    for(int i=0; i < people; i++){
        cout << "enter you first name and  last name " << endl;
        cin >> first;
        cin >> last;
        cout << "when is your birthday? DD/MM/YY"<< endl;
        cin >>day >> month >> year;

        birthday = new Date(day, month, year);


        information info(first, last, birthday); // create information that stores name last name and birth date
        stay.addInfo(info, i); // add the info to the Guests profile
        
        
        
        
    }
    cout << "which room would you like to pick?" << endl;
    cin >> roomNumber;
    
    bool available = manager.Gusts_Res_Request(checkin, checkout, roomNumber); // check if the room chosen is available or not
    
    if (!available){ // will end the program if room is taken
        break;
    }
    Guests_Res_Request reserve(checkin, checkout, stay); // create a new reservation request
    
    cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<< endl;
    cout <<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<< endl;
    cout <<"your id is :" << temp << endl;
    temp++;
    
    

    manager.addRequest(reserve, client); // to add the request to the array of requests
     
    client++;
    
    cout <<"in your room, there is:" << endl;
    for(int i =0; i<people; i++){
        stay.printGuests(i);    // to print the information of the guests that are in the same room
    }
    
    
   


    
    manager.editTable(checkin, checkout, roomNumber, reserve); // to add the id to the schedule
    manager.printTable(); // to print the new schedule
    cout << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << endl;
    
    
    
    }else if(menu ==2){
        int id;
       
        cout << "what is your id" << endl;
        cin >> id;
        manager.cancelReservation(id); // to cancel the reservation with a specific id and delete it from the schedule
        manager.printTable();

        
    }else if(menu ==3){
        cout <<"provide us with your id please: " << endl;
        int id;
        cin >> id;
        manager.findId(id); // search for the reservation that has a specific id
        
    }
    }



    

    return 0;
}