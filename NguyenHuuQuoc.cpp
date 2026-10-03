enum TrangThai
{
    CHO_KHAM,
    TAM_HOAN,
    DANG_KHAM,
    DA_KHAM
};

struct Patient
{
    string maBN;
    string HoTen;

    int MucDoKhanCap;
    Date ThoiDiemDangKy;

    TrangThai trangThai;
    bool isPriority;

    int heapIndex;

    Patient() {
        maBN = "";
        HoTen = "";
        MucDoKhanCap = 0;
        ThoiDiemDangKy = Date();
        
        isPriority = false;
        heapIndex = -1;
    }

    Patient(string id, string name, int urgency, Date timestamp) {
        maBN = id;
        HoTen = name;
        MucDoKhanCap = urgency;
        ThoiDiemDangKy = timestamp;

        trangThai = CHO_KHAM;
        isPriority = false;

        heapIndex = -1;
    }

    string EnumToString(TrangThai t) {
        if (t == CHO_KHAM) return "CHO_KHAM";
        if (t == TAM_HOAN) return "TAM_HOAN";
        if (t == DANG_KHAM) return "DANG_KHAM";
        return "DA_KHAM";
    }

    void PrintPatientInfo() {
        cout << "Ma benh nhan: " << maBN << el;
        cout << "Ten benh nhan: " << HoTen << el;
        cout << "Muc do khan cap cua benh nhan: " << MucDoKhanCap << el;
        cout << "Trang thai benh nhan: " << EnumToString(trangThai) << el;
        cout << "Thoi diem dang ky kham: ";
        ThoiDiemDangKy.PrintDate();
    }

};

struct HashTable
{
    vector < vector < pair<string, Patient*> > > myBucKet;

    int Size;

    HashTable(int size = 10000)
    {
        myBucKet.resize(size);
    }

    int hashFunction(string& key){
        ll hash = 0;

        for(char c : key){
            hash = hash * 31 + c;
        }

        return hash % myBucKet.size();
    }

    void Raw_insert(string& key, Patient* value){
        int HashIndex = hashFunction(key);

        if(find(key) == nullptr){
            myBucKet[HashIndex].push_back({key, value});
            Size++;
        }
    }

    void Resize(int newSize){
        vector < vector < pair<string, Patient*> > > old_myBucKet = myBucKet;
        
        myBucKet.clear();
        myBucKet.resize(newSize);

        Size = 0;
        for(auto& BucKet : old_myBucKet){
            for(auto& p : BucKet){
                Raw_insert(p.first, p.second);
            }
        }
    }
};

struct maxHeap
{
    int max_size = 100;
    Patient** a = new Patient* [max_size + 1];
    int size = 0;

   maxHeap(){
        size = 0;
    }

    void heapifyUp(int currIndex){
        int parentIndex = currIndex / 2;

        while(parentIndex > 0 and bigger(currIndex, parentIndex)){
            Swap(parentIndex, currIndex);

            currIndex = parentIndex;
            parentIndex = currIndex / 2;
        }
    }

    void heapifyDown(int currIndex){
        while(currIndex * 2 <= size){
            int leftChildIndex = currIndex * 2;
            int rightChildIndex = leftChildIndex + 1;
            int biggerChildIndex = leftChildIndex;

            if(rightChildIndex <= size and bigger(rightChildIndex, leftChildIndex)){
                biggerChildIndex = rightChildIndex;
            }

            if(bigger(biggerChildIndex, currIndex)){
                Swap(currIndex, biggerChildIndex);
                currIndex = biggerChildIndex;
            }
            else{
                break;
            }
        }
    }


    void Swap(int i, int j){
        swap(a[i], a[j]);

        a[i]->heapIndex = i;
        a[j]->heapIndex = j;
    }

    bool bigger(int i, int j){

        if(a[i]->isPriority == a[j]->isPriority){
            if(a[i]->MucDoKhanCap == a[j]->MucDoKhanCap){
                return a[i]->ThoiDiemDangKy < a[j]->ThoiDiemDangKy;
            }
            return a[i]->MucDoKhanCap > a[j]->MucDoKhanCap;
        }
        
        return a[i]->isPriority > a[j]->isPriority;
    }

    ~maxHeap(){
        delete[] a;
    }
};

struct PhongKham
{
    HashTable myHashTable;
    maxHeap myHeap;

    vector<Patient*> ListPatient;

    ~PhongKham(){
        for(auto& p : ListPatient){
            delete p;
        }

        ListPatient.clear();
    }

    bool DangKyKham(string& id, string& HoTen, int& MucDoKhanCap, Date ThoiDiemDangKy){
        if(myHashTable.find(id) != nullptr)  return false;
        else{
            Patient* p = new Patient(id, HoTen, MucDoKhanCap, ThoiDiemDangKy);

            if(!myHashTable.insert(id, p))
            {
                delete p;
                return false;
            }

            ListPatient.push_back(p);
            myHeap.add(p);

            return true;
        }
    }

    bool CapNhatMucDoUuTien(string& id, int& newMucDoKhanCap){
        Patient* p = myHashTable.find(id);

        if(p == nullptr || p->MucDoKhanCap == newMucDoKhanCap || p->trangThai != CHO_KHAM || newMucDoKhanCap < 0)  return false;

        myHeap.remove(p);
        p->MucDoKhanCap = newMucDoKhanCap;
        myHeap.add(p);

        return true;
    }

    int amountWaiting(){
        return myHeap.size;
    }
};

int main(){
    while(1){
        if(LuaChon == 8){
            int MucDoMoi;

            cout << "Nhap ma benh nhan can cap nhat: ";
            cin >> id;

            cout << el;

            cout << "Nhap muc do khan cap can cap nhat: ";
            cin >> MucDoMoi;

            cout << el;

            myDS.CapNhatMucDoUuTien(id, MucDoMoi);
        }

        if(LuaChon == 10){
            if(BNDangKham != nullptr){
                cout << "Van con benh nhan dang kham. Hay TamHoan sau do moi luu du lieu";
                continue;
            }
            Persistence::SaveToCSV(myDS);
        }

        if(LuaChon == 0){
            if(BNDangKham != nullptr){
                cout << "Van con benh nhan dang kham. Hay TamHoan sau do moi luu va thoat";
                continue;
            }
            cout << "Dang luu du lieu truoc khi thoat...\n";
            Persistence::SaveToCSV(myDS);
            break;
        }
    }
}