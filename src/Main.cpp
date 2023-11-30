#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Fawwas Aliy
 * 235150300111009
 * Teknik Komputer A
 */

class DBaseUser
{
public:
    ifstream in;
    ofstream out;
    string fileName;

    DBaseUser(const char *fileName)
    {
        DBaseUser::fileName = fileName;
    }

    void save(vector<string> *data)
    {
        DBaseUser::out.open(DBaseUser::fileName, ofstream::out | ofstream::trunc);
        sort((*data).begin(), (*data).end());
        (*data).erase(unique((*data).begin(), (*data).end()), (*data).end());
        for (auto x : (*data))
            DBaseUser::out << x << endl;
        DBaseUser::out.close();
    }

    vector<string> getDataUser()
    {

        DBaseUser::in.open(DBaseUser::fileName, ios::app);
        vector<string> data;
        string id, pass, saldo;
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
        while (!DBaseUser::in.eof())
        {
            DBaseUser::in >> id;
            DBaseUser::in >> pass;
            DBaseUser::in >> saldo;
            data.push_back(id + " " + pass + "  " + saldo);
        }
        DBaseUser::in.close();

        return data;
    }
};
class DBaseMenu
{
public:
    ifstream in;
    ofstream out;
    string fileName;

    DBaseMenu(const char *fileName)
    {
        DBaseMenu::fileName = fileName;
    }

    vector<string> eraseDuplicate(vector<string> *data)
    {
        sort((*data).begin(), (*data).end());
        (*data).erase(unique((*data).begin(), (*data).end()), (*data).end());
        return (*data);
    }

    void save(vector<string> *dataNama, vector<int> *dataHarga, vector<int> *dataStok)
    {
        DBaseMenu::out.open(DBaseMenu::fileName, ofstream::out | ofstream::trunc);
        vector<string> data;
        for (int i = 0; i < (*dataNama).size(); i++)
        {
            if ((*dataNama).at(i).find(' ') != -1)
                (*dataNama).at(i).replace((*dataNama).at(i).find(' '), 1, "_");
            data.push_back((*dataNama).at(i) + " " + to_string((*dataHarga).at(i)) + " " + to_string((*dataStok).at(i)));
        }
        data = eraseDuplicate(&data);
        for (auto it = data.begin(); it != data.end(); it++)
        {
            if (it == data.end() - 1)
                DBaseMenu::out << *it;
            else
                DBaseMenu::out << *it << endl;
        }
        DBaseMenu::out.close();
    }

    vector<string> getDataNama()
    {
        DBaseMenu::in.open(DBaseMenu::fileName, ios::app);
        vector<string> data;
        string nama, tempStr;
        while (!DBaseMenu::in.eof())
        {
            DBaseMenu::in >> nama;
            DBaseMenu::in >> tempStr;
            DBaseMenu::in >> tempStr;
            if (nama.find('_') != -1)
                nama.replace(nama.find('_'), 1, " ");
            data.push_back(nama);
        }
        DBaseMenu::in.close();
        return data;
    }
    vector<int> getDataHarga()
    {
        DBaseMenu::in.open(DBaseMenu::fileName, ios::app);
        vector<int> data;
        string tempStr;
        int harga;
        while (!DBaseMenu::in.eof())
        {
            DBaseMenu::in >> tempStr;
            DBaseMenu::in >> harga;
            DBaseMenu::in >> tempStr;
            data.push_back(harga);
        }
        DBaseMenu::in.close();
        return data;
    }
    vector<int> getDataStok()
    {
        DBaseMenu::in.open(DBaseMenu::fileName, ios::app);
        vector<int> data;
        string tempStr;
        int stok;
        while (!DBaseMenu::in.eof())
        {
            DBaseMenu::in >> tempStr;
            DBaseMenu::in >> tempStr;
            DBaseMenu::in >> stok;
            data.push_back(stok);
        }
        DBaseMenu::in.close();
        return data;
    }
};

void displayMenu(vector<string> *namaMenu, vector<int> *hargaMenu, vector<int> *stokMenu)
{
    cout << "  \tMenu\t\t\tHarga\t\tStok" << endl;
    for (int i = 0; i < (*namaMenu).size(); i++)
        if ((*namaMenu)[i].size() <= 6)
            cout << i + 1 << ".\t" << (*namaMenu)[i] << "\t\t\t" << (*hargaMenu)[i] << "\t\t" << (*stokMenu)[i] << endl;
        else if ((*namaMenu)[i].size() <= 15)
            cout << i + 1 << ".\t" << (*namaMenu)[i] << "\t\t" << (*hargaMenu)[i] << "\t\t" << (*stokMenu)[i] << endl;
        else
            cout << i + 1 << ".\t" << (*namaMenu)[i] << "\t" << (*hargaMenu)[i] << "\t\t" << (*stokMenu)[i] << endl;
}
void displayMenu2(vector<string> *namaMenu, vector<int> *hargaMenu, vector<int> *stokMenu)
{
    cout << "  \tMenu\t\t\tHarga\t\tStok" << endl;
    for (int i = 0; i < (*namaMenu).size(); i++)
        if ((*namaMenu)[i].size() <= 6)
            cout << "[" << i + 1 << "]\t" << (*namaMenu)[i] << "\t\t\t" << (*hargaMenu)[i] << "\t\t" << (*stokMenu)[i] << endl;
        else if ((*namaMenu)[i].size() <= 15)
            cout << "[" << i + 1 << "]\t" << (*namaMenu)[i] << "\t\t" << (*hargaMenu)[i] << "\t\t" << (*stokMenu)[i] << endl;
        else
            cout << "[" << i + 1 << "]\t" << (*namaMenu)[i] << "\t" << (*hargaMenu)[i] << "\t\t" << (*stokMenu)[i] << endl;
}

void garis(int x)
{
    if (x == 0)
        cout << "==========================================================" << endl;
    if (x == 1)
        cout << "----------------------------------------------------------" << endl;
}
void garis(string str)
{
    cout << "==========================================================" << endl;
    cout << str << endl;
    cout << "==========================================================" << endl;
}

int main()
{
    // deklarasi
    DBaseUser databaseUser = DBaseUser("src/User.bin");
    DBaseMenu databaseMenu = DBaseMenu("src/Menu.bin");

    vector<string> idCustomer = databaseUser.getDataUser();
    vector<string> dataNamaMenu = databaseMenu.getDataNama();
    vector<int> dataHargaMenu = databaseMenu.getDataHarga();
    vector<int> dataStokMenu = databaseMenu.getDataStok();
    string id, pass, tempStr, idAdmin = "Admin123 123Admin";
    int tempInt, saldo, duplicate;

    // main
    while (true)
    {
    LOGIN:
        system("cls");
        cout << "SELAMAT DATANG DI WARUNG AGUS" << endl;
        garis(0);
        cout << "[1] Login as Customer" << endl;
        cout << "[2] Login as Admin" << endl;
        cout << "[3] Login as Guests" << endl;
        cout << "[4] Register" << endl;
        cout << "[0] Exit" << endl;
        garis(0);
        cout << "> ";
        cin >> tempInt;

        // Customer
        if (tempInt == 1)
        {
            system("cls");
            cout << "Login as Customer [0] Back" << endl;
            garis(0);
            while (true)
            {
                cout << "> ID\t: ";
                cin >> id;
                if (id == "0")
                    goto LOGIN;
                cout << "> PASS\t: ";
                cin >> pass;
                for (auto x : idCustomer)
                    if (x.substr(0, x.find(" ")) == id && pass == x.substr(x.find(" ") + 1, x.length() - x.find(" ") - (x.length() - x.find("  ")) - 1))
                    {
                        saldo = stoi(x.substr(x.find("  ") + 2, x.length() - x.find("  ") - 2));
                        goto CUSTOMER;
                    }
                garis("ID tidak terdaftar atau Password salah");
            }
        CUSTOMER:
            while (true)
            {
                system("cls");
                cout << "WARUNG AGUS | " << id << " | Saldo: " << saldo << endl;
                garis(0);
                displayMenu(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);
                garis(0);
                cout << "[1] Beli" << endl;
                cout << "[2] Ganti Password" << endl;
                cout << "[0] Logout" << endl;
                garis(0);
                cout << "> ";
                cin >> tempInt;
                if (tempInt == 1)
                {
                    vector<int> notaNomer, notaJumlah, tempStokMenu = dataStokMenu;
                    int jumlah, total = 0, i = 0;
                    char pilihan;
                    while (true)
                    {
                        system("cls");
                        cout << "WARUNG AGUS | " << id << " | Saldo: " << saldo << " | Total: " << total + (total * 0.05) << endl;
                        garis(0);
                        displayMenu2(&dataNamaMenu, &dataHargaMenu, &tempStokMenu);
                        cout << "[t]\tTotal" << endl;
                        cout << "[0]\tKembali" << endl;
                        garis("harga belum termasuk PPN 5%");
                        cout << "> Nomer  : ";
                        cin >> pilihan;
                        if (pilihan == 't')
                        {
                            if (i == 0)
                            {
                                garis("anda belum memesan [0] Kembali");
                                cout << "> ";
                                cin >> tempInt;
                                continue;
                            }
                            break;
                        }
                        else if (int(pilihan - '0') == 0)
                            break;
                        else if (int(pilihan - '0') > dataNamaMenu.size() || int(pilihan - '0') < 0)
                        {
                            garis("tidak ada dimenu [0] Kembali");
                            cout << "> ";
                            cin >> tempInt;
                            continue;
                        }
                        cout << "> Jumlah : ";
                        cin >> jumlah;
                        if (tempStokMenu[int(pilihan - '0') - 1] < jumlah)
                        {
                            garis("maaf, stok tidak cukup [0] Kembali");
                            cout << "> ";
                            cin >> tempInt;
                            continue;
                        }
                        if (saldo < total + (total * 0.05) + (dataHargaMenu[int(pilihan - '0') - 1] * jumlah) + ((dataHargaMenu[int(pilihan - '0') - 1] * jumlah) * 0.05))
                        {
                            garis("saldo tidak mencukupi [0] Kembali");
                            cout << "> ";
                            cin >> tempInt;
                            continue;
                        }

                        duplicate = 0;
                        for (int j = 0; j < i; j++)
                            if (int(pilihan - '0') == notaNomer[j])
                            {
                                duplicate = 1;
                                total += dataHargaMenu[int(pilihan - '0') - 1] * jumlah;
                                tempStokMenu[int(pilihan - '0') - 1] -= jumlah;
                                notaJumlah[j] += jumlah;
                            }
                        if (duplicate == 0)
                        {
                            total += dataHargaMenu[int(pilihan - '0') - 1] * jumlah;
                            tempStokMenu[int(pilihan - '0') - 1] -= jumlah;
                            notaNomer.push_back(int(pilihan - '0'));
                            notaJumlah.push_back(jumlah);
                            i++;
                        }
                    }
                    if (int(pilihan - '0') != 0)
                    {
                        system("cls");
                        saldo -= total + (total * 0.05);
                        dataStokMenu = tempStokMenu;
                        cout << "NOTA WARUNG AGUS" << endl;
                        garis(0);
                        cout << "\tMenu\t\t\tHarga\tJumlah\tSubtotal" << endl;
                        for (int j = 0; j < i; j++)
                            if (dataNamaMenu[notaNomer[j] - 1].size() <= 6)
                                cout << j + 1 << ".\t" << dataNamaMenu[notaNomer[j] - 1] << "\t\t\t" << dataHargaMenu[notaNomer[j] - 1] << "\t" << notaJumlah[j] << "\t" << dataHargaMenu[notaNomer[j] - 1] * notaJumlah[j] << endl;
                            else if (dataNamaMenu[notaNomer[j] - 1].size() <= 15)
                                cout << j + 1 << ".\t" << dataNamaMenu[notaNomer[j] - 1] << "\t\t" << dataHargaMenu[notaNomer[j] - 1] << "\t" << notaJumlah[j] << "\t" << dataHargaMenu[notaNomer[j] - 1] * notaJumlah[j] << endl;
                            else
                                cout << j + 1 << ".\t" << dataNamaMenu[notaNomer[j] - 1] << "\t" << dataHargaMenu[notaNomer[j] - 1] << "\t" << notaJumlah[j] << "\t" << dataHargaMenu[notaNomer[j] - 1] * notaJumlah[j] << endl;
                        garis(1);
                        cout << "\t\t\t\tSubtotal      : " << total << endl;
                        cout << "\t\t\t\tPPN 5%        : " << total * 0.05 << endl;
                        garis(1);
                        cout << "\t\t\t\tTotal         : " << total + (total * 0.05) << endl;
                        garis("[0] Kembali");
                        cout << "> ";
                        cin >> tempInt;
                    }
                }
                else if (tempInt == 2)
                {
                    while (true)
                    {
                        system("cls");
                        cout << "GANTI PASSWORD" << endl;
                        garis(0);
                        cout << "> New Password\t\t: ";
                        cin >> pass;
                        cout << "> Confirm Password\t: ";
                        cin >> tempStr;
                        if (pass != tempStr)
                        {
                            garis("password tidak cocok [0] Kembali");
                            cout << "> ";
                            cin >> tempInt;
                            continue;
                        }
                        for (int i = 0; i < idCustomer.size(); i++)
                            if (idCustomer[i].substr(0, idCustomer[i].find(" ")) == id)
                            {
                                idCustomer[i].replace(idCustomer[i].find(" ") + 1, idCustomer[i].length() - idCustomer[i].find(" ") - (idCustomer[i].length() - idCustomer[i].find("  ")) - 1, pass);
                                break;
                            }
                        break;
                    }
                }
                else if (tempInt == 0)
                    break;
            }
            for (int i = 0; i < idCustomer.size(); i++)
                if (idCustomer[i].find(id) == 0)
                    idCustomer[i].replace(idCustomer[i].find("  ") + 2, idCustomer[i].length() - idCustomer[i].find("  ") - 2, to_string(saldo));
        }

        // Admin
        else if (tempInt == 2)
        {
            system("cls");
            cout << "Login as Admin [0] Back" << endl;
            garis(0);
            while (true)
            {
                cout << "> ID\t: ";
                cin >> id;
                if (id == "0")
                    goto LOGIN;
                cout << "> PASS\t: ";
                cin >> pass;
                if (idAdmin.substr(0, idAdmin.find(" ")) == id && pass == idAdmin.substr(idAdmin.find(" ") + 1, idAdmin.length() - idAdmin.find(" ")))
                    goto ADMIN;
                else if (pass == "0")
                    goto LOGIN;
                garis("ID tidak terdaftar atau Password salah");
            }
        ADMIN:
            while (true)
            {
                system("cls");
                cout << "WARUNG AGUS | ADMIN: " << id << endl;
                garis(0);
                displayMenu(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);
                garis(0);
                cout << "[1] Tambah Menu" << endl;
                cout << "[2] Hapus Menu" << endl;
                cout << "[3] Tambah Stok" << endl;
                cout << "[4] Tambah Saldo" << endl;
                cout << "[0] Logout" << endl;
                garis(0);
                cout << "> ";
                cin >> tempInt;
                if (tempInt == 1)
                {
                    while (true)
                    {
                        system("cls");
                        string namaMenu;
                        cout << "TAMBAH MENU" << endl;
                        garis(0);
                        displayMenu(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);
                        garis("[0]\tKembali");
                        cout << "spasi ditulis underscore '_' (maks.20 huruf)" << endl;
                        garis(0);
                        cout << "> Nama  : ";
                        cin >> namaMenu;
                        if (namaMenu == "0")
                            break;
                        while (true)
                            if (namaMenu.find('_') == -1)
                                break;
                            else
                                namaMenu.replace(namaMenu.find('_'), 1, " ");
                        if (namaMenu.size() <= 20)
                        {
                            dataNamaMenu.push_back(namaMenu);
                            cout << "> Harga : ";
                            cin >> tempInt;
                            dataHargaMenu.push_back(tempInt);
                            cout << "> Stok  : ";
                            cin >> tempInt;
                            dataStokMenu.push_back(tempInt);
                        }
                    }
                }
                else if (tempInt == 2)
                    while (true)
                    {
                        system("cls");
                        cout << "HAPUS MENU" << endl;
                        garis(0);
                        displayMenu2(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);
                        garis("[0]\tKembali");
                        cout << "> Nomer : ";
                        cin >> tempInt;
                        if (tempInt == 0)
                            break;
                        else if (tempInt > dataNamaMenu.size() || tempInt < 0)
                            continue;
                        dataNamaMenu.erase(dataNamaMenu.begin() + tempInt - 1);
                        dataHargaMenu.erase(dataHargaMenu.begin() + tempInt - 1);
                        dataStokMenu.erase(dataStokMenu.begin() + tempInt - 1);
                    }
                else if (tempInt == 3)
                {
                    int jumlah;
                    while (true)
                    {
                        system("cls");
                        cout << "TAMBAH STOK" << endl;
                        garis(0);
                        displayMenu2(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);
                        garis("[0]\tKembali");
                        cout << "> Nomer  : ";
                        cin >> tempInt;
                        if (tempInt == 0)
                            break;
                        else if (tempInt > dataNamaMenu.size() || tempInt < 0)
                            continue;
                        cout << "> Jumlah  : ";
                        cin >> jumlah;
                        dataStokMenu[tempInt - 1] += jumlah;
                    }
                }
                else if (tempInt == 4)
                {
                    tempInt = 1;
                    system("cls");
                    cout << "Tambah Saldo [0] Back" << endl;
                    garis(0);
                    while (true)
                    {
                        cout << "> ID\t: ";
                        cin >> tempStr;
                        if (tempStr == "0")
                            goto ADMIN;
                        for (int i = 0; i < idCustomer.size(); i++)
                        {
                            if (idCustomer[i].substr(0, idCustomer[i].find(" ")) == tempStr)
                            {
                                cout << "> Saldo\t: ";
                                cin >> tempInt;
                                saldo = tempInt + stoi(idCustomer[i].substr(idCustomer[i].find("  ") + 2, idCustomer[i].length() - idCustomer[i].find("  ") - 2));
                                idCustomer[i].replace(idCustomer[i].find("  ") + 2, idCustomer[i].length() - idCustomer[i].find("  ") - 2, to_string(saldo));
                                garis("berhasil ditambahkan");
                                break;
                            }
                            if (tempStr != "0" && i == idCustomer.size() - 1)
                                garis("ID tidak ditemukan");
                        }
                    }
                }
                else if (tempInt == 0)
                    break;
            }
        }

        // Guests
        else if (tempInt == 3)
        {
            system("cls");
            cout << "WARUNG AGUS | GUEST" << endl;
            garis(0);
            displayMenu(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);
            garis("[0] Logout");
            cout << "> ";
            cin >> tempInt;
        }

        // Register
        else if (tempInt == 4)
        {
            system("cls");
            cout << "Register [0] Back" << endl;
            garis(0);
            while (true)
            {
                cout << "> ID\t: ";
                cin >> id;
                if (id == "0")
                    goto LOGIN;
                cout << "> PASS\t: ";
                cin >> pass;
                cout << "> CONFIRM PASS\t: ";
                cin >> tempStr;
                duplicate = 0;
                for (auto x : idCustomer)
                    if (x.substr(0, x.find(" ")) == id)
                        duplicate = 1;
                if (pass == tempStr && duplicate == 0)
                {
                    idCustomer.push_back(id + " " + pass + "  50000");
                    goto LOGIN;
                }
                cout << "ID sudah tersedia atau confirm password salah" << endl;
            }
        }

        // Exit
        else if (tempInt == 0)
            break;
    }

    // Save data
    databaseUser.save(&idCustomer);
    databaseMenu.save(&dataNamaMenu, &dataHargaMenu, &dataStokMenu);

    return 0;
}