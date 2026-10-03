if(LuaChon == 4){
    Patient* p = myDS.GoiBNTiepTheo(BNDangKham);

    if(p != nullptr){
        p->PrintPatientInfo();
    }
    else{
        cout << "Khong co benh nhan nao trong danh sach cho" << el;
    }
}

struct Date {
    int day, month, year; 
    int hour, minute; 

    Date() {
        day = 0; month = 0; year = 0;
        hour = 0; minute = 0;
    }

    Date(int gio, int phut, int ngay, int thang, int nam) {
        hour = gio; minute = phut;
        day = ngay; month = thang; year = nam;
    }
    
    bool operator<(const Date& other) const {
        if(year != other.year) return year < other.year;
        if(month != other.month) return month < other.month;
        if(day != other.day) return day < other.day;
        if(hour != other.hour) return hour < other.hour;
        return minute < other.minute;
    }

    void PrintDate() {
        cout << setfill('0') << setw(2) << hour << ":" 
             << setfill('0') << setw(2) << minute << " ngay " 
             << setfill('0') << setw(2) << day << "/" 
             << setfill('0') << setw(2) << month << "/" 
             << year << el;
    }

    friend istream& operator>>(istream& in, Date& d) {
        char sepTime, sepDate1, sepDate2;
        
        cout << "Nhap thoi gian (HH:MM): ";
        in >> d.hour >> sepTime >> d.minute; 

        cout << " Nhap ngay thang (DD/MM/YYYY): ";
        in >> d.day >> sepDate1 >> d.month >> sepDate2 >> d.year;

        bool formatError = in.fail() || sepTime != ':' || sepDate1 != '/' || sepDate2 != '/';
        bool timeError = (d.hour < 0 || d.hour > 23) || (d.minute < 0 || d.minute > 59);
        bool dateError = false;
        if (d.year < 1900 || d.month < 1 || d.month > 12) {
            dateError = true;
        } else {
            int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            
            if ((d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0)) {
                daysInMonth[2] = 29;
            }

            if (d.day < 1 || d.day > daysInMonth[d.month]) {
                dateError = true; 
            }
        }
        if(formatError || timeError || dateError) {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nLOI: Nhap sai dinh dang! Vui long dung dung dau ':' cho gio va '/' cho ngay.\n";
            cout << "Goi y: Gio (0-23), Phut (0-59), Ngay thang phai co thuc.\n";
            d.day = d.month = d.year = d.hour = d.minute = 0;
        }
        return in;
        
    }
};

void Resize(int new_max){
    Patient** new_a = new Patient*[new_max + 1];
    for (int i = 1; i <= size; i++) {
        new_a[i] = a[i];
    }
    delete[] a;
    a = new_a;
    max_size = new_max;
}

Patient* peek(){
    if(!isEmpty()){
        return a[1];
    }

    return nullptr;
}

bool isEmpty(){
    return size <= 0;
}

void add(Patient* v){
    size++;
    a[size] = v;
    v->heapIndex = size;

    if (size >= max_size) {
        Resize(max_size * 2);
    }

    int currIndex = size;
    heapifyUp(currIndex);
}

Patient* poll(){
    if(isEmpty()){
        return nullptr;
    }

    Patient* root = a[1];
    root->heapIndex = -1;

    if(size > 1){
        a[1] = a[size];
        a[1]->heapIndex = 1;
    }

    size--;

    if (size > 0) {
        heapifyDown(1);
    }

    return root;
}   