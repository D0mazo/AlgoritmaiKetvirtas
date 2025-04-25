//Duotas dvikryptis sąrašas, kuriame skaičiai gali kartotis. Sukurti vienkryptį sąrašą į
//kurį pakliūna tik nepasikartojantys skaičiai.

#include <iostream>

struct DvikryptisMazgas {
    int duomuo;
    DvikryptisMazgas* ankstesnis;
    DvikryptisMazgas* kitas;
    DvikryptisMazgas(int d) : duomuo(d), ankstesnis(nullptr), kitas(nullptr) {}
};

struct VienkryptisMazgas {
    int duomuo;
    VienkryptisMazgas* kitas;
    VienkryptisMazgas(int d) : duomuo(d), kitas(nullptr) {}
};

DvikryptisMazgas* iterptiDvikrypti(DvikryptisMazgas* pradzios, int duomuo) {
    DvikryptisMazgas* naujasMazgas = new DvikryptisMazgas(duomuo);
    if (!pradzios) return naujasMazgas;
    DvikryptisMazgas* einamasis = pradzios;
    while (einamasis->kitas) einamasis = einamasis->kitas;
    einamasis->kitas = naujasMazgas;
    naujasMazgas->ankstesnis = einamasis;
    return pradzios;
}

VienkryptisMazgas* iterptiVienkrypti(VienkryptisMazgas* pradzios, int duomuo) {
    VienkryptisMazgas* naujasMazgas = new VienkryptisMazgas(duomuo);
    if (!pradzios) return naujasMazgas;
    VienkryptisMazgas* einamasis = pradzios;
    while (einamasis->kitas) einamasis = einamasis->kitas;
    einamasis->kitas = naujasMazgas;
    return pradzios;
}

int skaiciuotiPasikartojimus(DvikryptisMazgas* pradzios, int duomuo) {
    int kiekis = 0;
    DvikryptisMazgas* einamasis = pradzios;
    while (einamasis) {
        if (einamasis->duomuo == duomuo) kiekis++;
        einamasis = einamasis->kitas;
    }
    return kiekis;
}

VienkryptisMazgas* sukurtiUnikaliuSarasa(DvikryptisMazgas* dvikryptisPradzios) {
    VienkryptisMazgas* vienkryptisPradzios = nullptr;
    DvikryptisMazgas* einamasis = dvikryptisPradzios;
    while (einamasis) {
        if (skaiciuotiPasikartojimus(dvikryptisPradzios, einamasis->duomuo) == 1) {
            vienkryptisPradzios = iterptiVienkrypti(vienkryptisPradzios, einamasis->duomuo);
        }
        einamasis = einamasis->kitas;
    }
    return vienkryptisPradzios;
}

void spausdintiDvikryptiSarasa(DvikryptisMazgas* pradzios) {
    DvikryptisMazgas* einamasis = pradzios;
    while (einamasis) {
        std::cout << einamasis->duomuo << " ";
        einamasis = einamasis->kitas;
    }
    std::cout << std::endl;
}

void spausdintiVienkryptiSarasa(VienkryptisMazgas* pradzios) {
    VienkryptisMazgas* einamasis = pradzios;
    while (einamasis) {
        std::cout << einamasis->duomuo << " ";
        einamasis = einamasis->kitas;
    }
    std::cout << std::endl;
}

void atlaisvintiDvikryptiSarasa(DvikryptisMazgas* pradzios) {
    DvikryptisMazgas* einamasis = pradzios;
    while (einamasis) {
        DvikryptisMazgas* laikinas = einamasis;
        einamasis = einamasis->kitas;
        delete laikinas;
    }
}

void atlaisvintiVienkryptiSarasa(VienkryptisMazgas* pradzios) {
    VienkryptisMazgas* einamasis = pradzios;
    while (einamasis) {
        VienkryptisMazgas* laikinas = einamasis;
        einamasis = einamasis->kitas;
        delete laikinas;
    }
}

void ivestiDvikryptiSarasa(DvikryptisMazgas*& pradzios) {
    int n;
    std::cout << "Iveskite skaiciu kieki: ";
    std::cin >> n;
    atlaisvintiDvikryptiSarasa(pradzios);
    pradzios = nullptr;
    std::cout << "Iveskite " << n << " skaicius: ";
    for (int i = 0; i < n; i++) {
        int duomuo;
        std::cin >> duomuo;
        pradzios = iterptiDvikrypti(pradzios, duomuo);
    }
}

int main() {
    DvikryptisMazgas* dvikryptisPradzios = nullptr;
    VienkryptisMazgas* vienkryptisPradzios = nullptr;
    int pasirinkimas;

    do {
        std::cout << "\n1. Ivesti dvikrypti sarasa\n";
        std::cout << "2. Sukurti vienkrypti sarasa su nepasikartojanciais skaiciais\n";
        std::cout << "3. Spausdinti dvikrypti sarasa\n";
        std::cout << "4. Spausdinti vienkrypti sarasa\n";
        std::cout << "0. Baigti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                ivestiDvikryptiSarasa(dvikryptisPradzios);
                break;
            case 2:
                atlaisvintiVienkryptiSarasa(vienkryptisPradzios);
                vienkryptisPradzios = sukurtiUnikaliuSarasa(dvikryptisPradzios);
                break;
            case 3:
                if (dvikryptisPradzios) spausdintiDvikryptiSarasa(dvikryptisPradzios);
                else std::cout << "Dvikryptis sarasas tuscias\n";
                break;
            case 4:
                if (vienkryptisPradzios) spausdintiVienkryptiSarasa(vienkryptisPradzios);
                else std::cout << "Vienkryptis sarasas tuscias\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Neteisingas pasirinkimas\n";
        }
    } while (pasirinkimas != 0);

    atlaisvintiDvikryptiSarasa(dvikryptisPradzios);
    atlaisvintiVienkryptiSarasa(vienkryptisPradzios);
    return 0;
}