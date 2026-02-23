/*
 * Análise de produção de bb̄ em colisões O-O
 * Identifica quarks b ou hádrons B e analisa o sistema BB
 *
 * Compilar: g++ -o analyze_bb analyze_bb.cpp `root-config --cflags --libs`
 * Executar: ./analyze_bb input.root output.root [cross_section_nb]
 */

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

// Contadores
double weight = 0.0;
double xs = 0.0;   // nb isospin nPDFSet0
double lumi = 1.0; // nb-1

int main(int argc, char **argv)
{

    if (argc < 3)
    {
        std::cout << "Uso: " << argv[0] << " <input.root> <output.root> [cross_section_nb]" << std::endl;
        std::cout << "  cross_section_nb: seção de choque em nb (opcional)" << std::endl;
        return 1;
    }

    std::string output_name = argv[2];

    // Seção de choque fornecida como argumento (opcional)
    if (argc >= 4)
    {
        xs = std::atof(argv[3]);
        std::cout << "Seção de choque fornecida: " << xs << " nb" << std::endl;
    }
    else
    {
        std::cout << "Seção de choque padrão: " << xs << " nb" << std::endl;
    }

    // Abrir arquivo de entrada
    TFile *input_file = TFile::Open(argv[1]);
    if (!input_file || input_file->IsZombie())
    {
        std::cerr << "Erro ao abrir arquivo: " << argv[1] << std::endl;
        return 1;
    }

    // Obter a árvore
    TTree *tree = (TTree *)input_file->Get("lheTree");
    if (!tree)
    {
        std::cerr << "Erro: árvore 'lheTree' não encontrada!" << std::endl;
        input_file->Close();
        return 1;
    }

    // Variáveis para leitura
    std::vector<int> *pdgID = nullptr;
    std::vector<int> *status = nullptr;
    std::vector<float> *px = nullptr;
    std::vector<float> *py = nullptr;
    std::vector<float> *pz = nullptr;
    std::vector<float> *e = nullptr;
    std::vector<float> *m = nullptr;

    tree->SetBranchAddress("pdgID", &pdgID);
    tree->SetBranchAddress("status", &status);
    tree->SetBranchAddress("px", &px);
    tree->SetBranchAddress("py", &py);
    tree->SetBranchAddress("pz", &pz);
    tree->SetBranchAddress("e", &e);
    tree->SetBranchAddress("m", &m);

    // Histogramas
    TH1F *h_top_pt = new TH1F("h_top_pt", "pT dos tops;pT_{top} [GeV];Eventos", 100, 0, 4000);
    TH1F *h_ntop = new TH1F("h_ntop", "NTops;N_{top};Eventos", 10, 0, 10);

    Long64_t nEntries = tree->GetEntries();
    std::cout << "Processando " << nEntries << " eventos..." << std::endl;
    TLorentzVector top;

    // Loop sobre eventos
    for (Long64_t iEvent = 0; iEvent < nEntries; iEvent++)
    {
        int n_top = 0;
        tree->GetEntry(iEvent);

        weight = xs * lumi / nEntries;

        for (size_t iPart = 0; iPart < pdgID->size(); iPart++)
        {
            int pdg = fabs(pdgID->at(iPart));
            int stat = status->at(iPart);

            if (pdg == 6 && stat == 1)
            {
                top.SetPxPyPzE(px->at(iPart), py->at(iPart), pz->at(iPart), e->at(iPart));
                h_top_pt->Fill(top.Pt(), weight);
                n_top++;
            }
        }
        h_ntop->Fill(n_top, weight);

        // Progresso
        if (iEvent % 1000 == 0)
        {
            std::cout << "Processado: " << iEvent << " / " << nEntries
                      << " (" << (100.0 * iEvent / nEntries) << "%)" << std::endl;
        }
    }

    // Salvar histogramas
    TFile *output_file = new TFile(output_name.c_str(), "RECREATE");

    h_top_pt->Write();
    h_ntop->Write();

    output_file->Close();

    std::cout << "\nHistogramas salvos em: " << output_name << std::endl;
    std::cout << "Arquivo de análise salvo em: out_bbbar.txt" << std::endl;

    // Fechar arquivo de entrada
    input_file->Close();
    delete input_file;
    delete output_file;

    return 0;
}