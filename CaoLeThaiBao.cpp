//Xử lý logic ưu tiên cực trị của YC2
bool bigger(int i, int j){
        if(a[i]->isPriority == a[j]->isPriority){
            if(a[i]->MucDoKhanCap == a[j]->MucDoKhanCap){
                return a[i]->ThoiDiemDangKy < a[j]->ThoiDiemDangKy;
            }
            return a[i]->MucDoKhanCap > a[j]->MucDoKhanCap;
        }
        
        return a[i]->isPriority > a[j]->isPriority;
    }
//Xử lý nghiệp vụ hoãn và đưa bệnh nhân quay lại hàng đợi
bool TamHoan(Patient*& BNDangKham){
        if(BNDangKham == nullptr || BNDangKham->trangThai != DANG_KHAM) return false;

        Patient* p = BNDangKham;
        p->isPriority = true;
        p->trangThai = TAM_HOAN;
        BNDangKham = nullptr;

        return true;
    }

bool TiepTucKham(string& id){
        Patient* p = myHashTable.find(id);

        if (p == nullptr) return false;

        if(p->trangThai != TAM_HOAN) return false;

        p->trangThai = CHO_KHAM;
        myHeap.add(p);

        return true;
    }
//tầng đọc/ghi dữ liệu CSV
struct Persistence {
    static string EnumToString(TrangThai t) {
        if (t == CHO_KHAM) return "CHO_KHAM";
        if (t == TAM_HOAN) return "TAM_HOAN";
        if (t == DANG_KHAM) return "DANG_KHAM";
        return "DA_KHAM";
    }

    static TrangThai StringToEnum(const string& s) {
        if (s == "TAM_HOAN") return TAM_HOAN;
        if (s == "DANG_KHAM") return DANG_KHAM;
        if (s == "DA_KHAM") return DA_KHAM;
        return CHO_KHAM;
    }

    static void SaveToCSV(PhongKham& pk, const string& filename = "patients.csv") {
        ofstream fout(filename);
        if (!fout.is_open()) {
            cout << "Loi: Khong the mo file de ghi!\n";
            return;
        }
        
        for (Patient* p : pk.ListPatient) {
            fout << p->maBN << ","
                 << p->HoTen << ","
                 << p->MucDoKhanCap << ","
                 << p->ThoiDiemDangKy.day << ","
                 << p->ThoiDiemDangKy.month << ","
                 << p->ThoiDiemDangKy.year << ","
                 << p->ThoiDiemDangKy.hour << ","
                 << p->ThoiDiemDangKy.minute << ","
                 << p->isPriority << ","
                 << EnumToString(p->trangThai) << "\n";
        }
    
        fout.close();
        cout << "Luu du lieu vao file '" << filename << "' thanh cong!\n";
    }

    static void LoadFromCSV(PhongKham& pk, const string& filename = "patients.csv") {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cout << "Chua co du lieu cu, khoi tao danh sach rong.\n";
            return;
        }

        string line;

        while (getline(fin, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string maBN, hoTen, mucDoStr, ngayStr, thangStr, namStr, gioStr, phutStr, trangThaiStr, isPriorityStr;

            getline(ss, maBN, ',');
            getline(ss, hoTen, ',');
            getline(ss, mucDoStr, ',');
            getline(ss, ngayStr, ',');
            getline(ss, thangStr, ',');
            getline(ss, namStr, ',');
            getline(ss, gioStr, ',');
            getline(ss, phutStr, ',');
            getline(ss, isPriorityStr, ',');
            getline(ss, trangThaiStr, ',');

            int mucDo = stoi(mucDoStr);
            Date thoiDiem(stoi(gioStr), stoi(phutStr),  stoi(ngayStr), stoi(thangStr), stoi(namStr));
            
            if(!pk.DangKyKham(maBN, hoTen, mucDo, thoiDiem)) continue;

            Patient* p = pk.TraCuuHoSo(maBN);
            if (p != nullptr) {
                p->isPriority = stoi(isPriorityStr);
                p->trangThai = StringToEnum(trangThaiStr);
                
                pk.myHeap.remove(p);

                if(p->trangThai == CHO_KHAM){
                    pk.myHeap.add(p);
                }
            }
        }
        fin.close();
        cout << "Nap du lieu tu file thanh cong!\n";
    }
};
