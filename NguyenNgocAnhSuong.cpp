if(LuaChon == 2){
     cout << "Nhap ma BN can tra cuu: ";
     cin >> id;
            
     Patient* p = myDS.TraCuuHoSo(id);
     if(p != nullptr){
         p->PrintPatientInfo();
     }
     else{
         cout << "Khong tim thay benh nhan" << el;
     }
}
struct HashTable {
    Patient* find(string& key){
        int HashIndex = hashFunction(key);

        for(auto& x : myBucKet[HashIndex]){
            if(x.first == key)  return x.second;
        }

        return nullptr;
    }
    bool insert(string& key, Patient* value){
        int HashIndex = hashFunction(key);

        if(find(key) == nullptr){
            myBucKet[HashIndex].push_back({key, value});
            Size++;

            if((double) Size / myBucKet.size() > 0.75){
                Resize(myBucKet.size() * 2);
            }
            return true;
        }

        return false;
    }

};
struct PhongKham {
    Patient* TraCuuHoSo(string& id){
        return myHashTable.find(id);
    }
};
