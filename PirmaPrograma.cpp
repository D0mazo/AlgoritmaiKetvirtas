//Sukurti AVL medį, realizuojant elemento įterpimo, pašalinimo, spausdinimo bei
//paieškos funkcijas. Perkelti to sąrašo visus elementus vienkryptį ciklinį sąrašą.
//Atspausdinti visus sąrašo elementus.

#include <iostream>

struct MedzioMazgas {
    int duomuo;
    MedzioMazgas* kairysis;
    MedzioMazgas* desinysis;
    int aukstis;
    MedzioMazgas(int d) : duomuo(d), kairysis(nullptr), desinysis(nullptr), aukstis(1) {}
};

struct SarasasMazgas {
    int duomuo;
    SarasasMazgas* kitas;
    SarasasMazgas(int d) : duomuo(d), kitas(nullptr) {}
};

int gautiAuksti(MedzioMazgas* mazgas) {
    return mazgas ? mazgas->aukstis : 0;
}

int gautiBalansa(MedzioMazgas* mazgas) {
    return mazgas ? gautiAuksti(mazgas->kairysis) - gautiAuksti(mazgas->desinysis) : 0;
}

MedzioMazgas* desinysisSukimas(MedzioMazgas* y) {
    MedzioMazgas* x = y->kairysis;
    MedzioMazgas* T2 = x->desinysis;
    x->desinysis = y;
    y->kairysis = T2;
    y->aukstis = std::max(gautiAuksti(y->kairysis), gautiAuksti(y->desinysis)) + 1;
    x->aukstis = std::max(gautiAuksti(x->kairysis), gautiAuksti(x->desinysis)) + 1;
    return x;
}

MedzioMazgas* kairysisSukimas(MedzioMazgas* x) {
    MedzioMazgas* y = x->desinysis;
    MedzioMazgas* T2 = y->kairysis;
    y->kairysis = x;
    x->desinysis = T2;
    x->aukstis = std::max(gautiAuksti(x->kairysis), gautiAuksti(x->desinysis)) + 1;
    y->aukstis = std::max(gautiAuksti(y->kairysis), gautiAuksti(y->desinysis)) + 1;
    return y;
}

MedzioMazgas* iterptiMedzioMazga(MedzioMazgas* pradzios, int duomuo) {
    if (!pradzios) return new MedzioMazgas(duomuo);
    if (duomuo < pradzios->duomuo) pradzios->kairysis = iterptiMedzioMazga(pradzios->kairysis, duomuo);
    else pradzios->desinysis = iterptiMedzioMazga(pradzios->desinysis, duomuo);
    pradzios->aukstis = std::max(gautiAuksti(pradzios->kairysis), gautiAuksti(pradzios->desinysis)) + 1;
    int balansas = gautiBalansa(pradzios);
    if (balansas > 1 && duomuo < pradzios->kairysis->duomuo) return desinysisSukimas(pradzios);
    if (balansas < -1 && duomuo > pradzios->desinysis->duomuo) return kairysisSukimas(pradzios);
    if (balansas > 1 && duomuo > pradzios->kairysis->duomuo) {
        pradzios->kairysis = kairysisSukimas(pradzios->kairysis);
        return desinysisSukimas(pradzios);
    }
    if (balansas < -1 && duomuo < pradzios->desinysis->duomuo) {
        pradzios->desinysis = desinysisSukimas(pradzios->desinysis);
        return kairysisSukimas(pradzios);
    }
    return pradzios;
}

MedzioMazgas* rastiMinimuma(MedzioMazgas* pradzios) {
    while (pradzios && pradzios->kairysis) pradzios = pradzios->kairysis;
    return pradzios;
}

MedzioMazgas* pasalintiMedzioMazga(MedzioMazgas* pradzios, int duomuo) {
    if (!pradzios) return nullptr;
    if (duomuo < pradzios->duomuo) pradzios->kairysis = pasalintiMedzioMazga(pradzios->kairysis, duomuo);
    else if (duomuo > pradzios->duomuo) pradzios->desinysis = pasalintiMedzioMazga(pradzios->desinysis, duomuo);
    else {
        if (!pradzios->kairysis) {
            MedzioMazgas* temp = pradzios->desinysis;
            delete pradzios;
            return temp;
        }
        if (!pradzios->desinysis) {
            MedzioMazgas* temp = pradzios->kairysis;
            delete pradzios;
            return temp;
        }
        MedzioMazgas* min = rastiMinimuma(pradzios->desinysis);
        pradzios->duomuo = min->duomuo;
        pradzios->desinysis = pasalintiMedzioMazga(pradzios->desinysis, min->duomuo);
    }
    pradzios->aukstis = std::max(gautiAuksti(pradzios->kairysis), gautiAuksti(pradzios->desinysis)) + 1;
    int balansas = gautiBalansa(pradzios);
    if (balansas > 1 && gautiBalansa(pradzios->kairysis) >= 0) return desinysisSukimas(pradzios);
    if (balansas > 1 && gautiBalansa(pradzios->kairysis) < 0) {
        pradzios->kairysis = kairysisSukimas(pradzios->kairysis);
        return desinysisSukimas(pradzios);
    }
    if (balansas < -1 && gautiBalansa(pradzios->desinysis) <= 0) return kairysisSukimas(pradzios);
    if (balansas < -1 && gautiBalansa(pradzios->desinysis) > 0) {
        pradzios->desinysis = desinysisSukimas(pradzios->desinysis);
        return kairysisSukimas(pradzios);
    }
    return pradzios;
}

MedzioMazgas* ieskotiMedzioMazga(MedzioMazgas* pradzios, int duomuo) {
    if (!pradzios || pradzios->duomuo == duomuo) return pradzios;
    if (duomuo < pradzios->duomuo) return ieskotiMedzioMazga(pradzios->kairysis, duomuo);
    return ieskotiMedzioMazga(pradzios->desinysis, duomuo);
}

void spausdintiMedi(MedzioMazgas* pradzios) {
    if (pradzios) {
        spausdintiMedi(pradzios->kairysis);
        std::cout << pradzios->duomuo << " ";
        spausdintiMedi(pradzios->desinysis);
    }
}

SarasasMazgas* iterptiSarasoMazga(SarasasMazgas* pradzios, int duomuo) {
    SarasasMazgas* naujasMazgas = new SarasasMazgas(duomuo);
    if (!pradzios) {
        naujasMazgas->kitas = naujasMazgas;
        return naujasMazgas;
    }
    SarasasMazgas* einamasis = pradzios;
    while (einamasis->kitas != pradzios) einamasis = einamasis->kitas;
    einamasis->kitas = naujasMazgas;
    naujasMazgas->kitas = pradzios;
    return pradzios;
}

SarasasMazgas* perkeltiISarasa(MedzioMazgas* medzioPradzios, SarasasMazgas* sarasoPradzios) {
    if (medzioPradzios) {
        sarasoPradzios = perkeltiISarasa(medzioPradzios->kairysis, sarasoPradzios);
        sarasoPradzios = iterptiSarasoMazga(sarasoPradzios, medzioPradzios->duomuo);
        sarasoPradzios = perkeltiISarasa(medzioPradzios->desinysis, sarasoPradzios);
    }
    return sarasoPradzios;
}

void spausdintiSarasa(SarasasMazgas* pradzios) {
    if (!pradzios) {
        std::cout << "Sarasas tuscias\n";
        return;
    }
    SarasasMazgas* einamasis = pradzios;
    do {
        std::cout << einamasis->duomuo << " ";
        einamasis = einamasis->kitas;
    } while (einamasis != pradzios);
    std::cout << std::endl;
}

void atlaisvintiMedi(MedzioMazgas* pradzios) {
    if (pradzios) {
        atlaisvintiMedi(pradzios->kairysis);
        atlaisvintiMedi(pradzios->desinysis);
        delete pradzios;
    }
}

void atlaisvintiSarasa(SarasasMazgas* pradzios) {
    if (!pradzios) return;
    SarasasMazgas* einamasis = pradzios;
    SarasasMazgas* pradinis = pradzios;
    do {
        SarasasMazgas* laikinas = einamasis;
        einamasis = einamasis->kitas;
        delete laikinas;
    } while (einamasis != pradinis);
}

int main() {
    MedzioMazgas* medzioPradzios = nullptr;
    SarasasMazgas* sarasoPradzios = nullptr;
    int pasirinkimas, duomuo;

    do {
        std::cout << "\n1. Iterpti elementa i medi\n";
        std::cout << "2. Pasalinti elementa is medzio\n";
        std::cout << "3. Ieskoti elemento medyje\n";
        std::cout << "4. Spausdinti medi\n";
        std::cout << "5. Perkelti medzio elementus i ciklinį sarasa\n";
        std::cout << "6. Spausdinti ciklinį sarasa\n";
        std::cout << "0. Baigti\n";
        std::cout << "Pasirinkite: ";
        std::cin >> pasirinkimas;

        switch (pasirinkimas) {
            case 1:
                std::cout << "Iveskite elementa: ";
                std::cin >> duomuo;
                medzioPradzios = iterptiMedzioMazga(medzioPradzios, duomuo);
                break;
            case 2:
                std::cout << "Iveskite pasalinama elementa: ";
                std::cin >> duomuo;
                medzioPradzios = pasalintiMedzioMazga(medzioPradzios, duomuo);
                break;
            case 3:
                std::cout << "Iveskite ieskoma elementa: ";
                std::cin >> duomuo;
                if (ieskotiMedzioMazga(medzioPradzios, duomuo)) std::cout << "Elementas rastas\n";
                else std::cout << "Elementas nerastas\n";
                break;
            case 4:
                if (medzioPradzios) spausdintiMedi(medzioPradzios);
                else std::cout << "Medis tuscias\n";
                std::cout << std::endl;
                break;
            case 5:
                atlaisvintiSarasa(sarasoPradzios);
                sarasoPradzios = nullptr;
                sarasoPradzios = perkeltiISarasa(medzioPradzios, sarasoPradzios);
                break;
            case 6:
                spausdintiSarasa(sarasoPradzios);
                break;
            case 0:
                break;
            default:
                std::cout << "Neteisingas pasirinkimas\n";
        }
    } while (pasirinkimas != 0);

    atlaisvintiMedi(medzioPradzios);
    atlaisvintiSarasa(sarasoPradzios);
    return 0;
}
