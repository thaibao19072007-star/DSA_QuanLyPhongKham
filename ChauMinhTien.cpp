struct HashTable {
    vector < vector < pair<string, Patient*> > > myBucKet;
    int Size = 0;

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
 bool erase(string& key){
        int HashIndex = hashFunction(key);
        for(int i = 0; i < myBucKet[HashIndex].size(); i++){
            if(myBucKet[HashIndex][i].first == key){
                myBucKet[HashIndex].erase(myBucKet[HashIndex].begin() + i);
                Size--;
                return true;
            }
        }
        return false;
    }
struct PhongKham {
    HashTable myHashTable;
    maxHeap myHeap;
    vector < Patient* > ListPatient;

    ~PhongKham(){
        for(auto& p : ListPatient){
            delete p;
        }

        ListPatient.clear();
    }
      bool HuyLuotKham(string& id){
        Patient* p = myHashTable.find(id);

        if(p == nullptr || p->trangThai != CHO_KHAM) return false;
        
        myHashTable.erase(id);
        myHeap.remove(p);

        for(int i = 0; i < ListPatient.size(); i++){
            if(ListPatient[i] == p){
                ListPatient.erase(ListPatient.begin() + i);
                break;
            }
        }

        delete p;
        return true;
    }
        if(LuaChon == 5){
            cout << "Nhap ma BN can huy kham: ";
            cin >> id;

            if(myDS.HuyLuotKham(id)){
                cout << "Huy luot kham thanh cong!" << el;
            }
            else{
                cout << "Khong tim thay benh nhan de huy!" << el;
            }
        }
