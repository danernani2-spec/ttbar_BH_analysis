/*
 * Programa básico para ler árvore ROOT de LHE
 * Produção de tops em colisões O-O
 * 
 * Compilar: g++ -o read_lhe_tree read_lhe_tree.cpp `root-config --cflags --libs`
 * Executar: ./read_lhe_tree input.root
 */

#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{

  if(argc < 2)
  {
    std::cout << "Uso: " << argv[0] << " <arquivo.root>" << std::endl;
    return 1;
  }

  // Abrir arquivo ROOT
  TFile *file = TFile::Open(argv[1]);
  if(!file || file->IsZombie())
  {
    std::cerr << "Erro ao abrir arquivo: " << argv[1] << std::endl;
    return 1;
  }

  // Obter a árvore
  TTree *tree = (TTree *)file->Get("lheTree");
  if(!tree)
  {
    std::cerr << "Erro: árvore 'lheTree' não encontrada!" << std::endl;
    file->Close();
    return 1;
  }

  // Variáveis para leitura dos branches
  std::vector<int> *pdgID = nullptr;
  std::vector<int> *status = nullptr;
  std::vector<float> *px = nullptr;
  std::vector<float> *py = nullptr;
  std::vector<float> *pz = nullptr;
  std::vector<float> *e = nullptr;
  std::vector<float> *m = nullptr;

  // Configurar branches
  tree->SetBranchAddress("pdgID", &pdgID);
  tree->SetBranchAddress("status", &status);
  tree->SetBranchAddress("px", &px);
  tree->SetBranchAddress("py", &py);
  tree->SetBranchAddress("pz", &pz);
  tree->SetBranchAddress("e", &e);
  tree->SetBranchAddress("m", &m);

  Long64_t nEntries = tree->GetEntries();
  std::cout << "Número total de eventos: " << nEntries << std::endl;

  // Loop sobre os eventos
  for(Long64_t iEvent = 0; iEvent < nEntries; iEvent++)
  {
    tree->GetEntry(iEvent);

    // Imprimir informação do evento (exemplo: primeiros 5 eventos)
    if(iEvent < 5)
    {
      std::cout << "\n========== Evento " << iEvent << " ==========" << std::endl;
      std::cout << "Número de partículas: " << pdgID->size() << std::endl;

      // Loop sobre as partículas
      for(size_t iPart = 0; iPart < pdgID->size(); iPart++)
      {
        std::cout << "\nPartícula " << iPart << ":" << std::endl;
        std::cout << "  pdgID  : " << pdgID->at(iPart) << std::endl;
        std::cout << "  status : " << status->at(iPart) << std::endl;
        std::cout << "  px     : " << px->at(iPart) << " GeV" << std::endl;
        std::cout << "  py     : " << py->at(iPart) << " GeV" << std::endl;
        std::cout << "  pz     : " << pz->at(iPart) << " GeV" << std::endl;
        std::cout << "  E      : " << e->at(iPart) << " GeV" << std::endl;
        std::cout << "  massa  : " << m->at(iPart) << " GeV" << std::endl;

        // Calcular pT (momento transverso)
        float pt = sqrt(px->at(iPart) * px->at(iPart) + py->at(iPart) * py->at(iPart));
        std::cout << "  pT     : " << pt << " GeV" << std::endl;

        // Identificar tops (pdgID = 6 para top, -6 para anti-top)
        if(abs(pdgID->at(iPart)) == 6)
        {
          std::cout << "  >>> TOP QUARK ENCONTRADO! <<<" << std::endl;
        }
      }
    }

    // Análise estatística para todos os eventos
    // Exemplo: contar tops
    int nTops = 0;
    for(size_t iPart = 0; iPart < pdgID->size(); iPart++)
    {
      if(abs(pdgID->at(iPart)) == 6 && status->at(iPart) == 1)
      {
        nTops++;
      }
    }

    if(iEvent % 100 == 0)
    {
      std::cout << "Processando evento " << iEvent << " / " << nEntries
                << " (" << (100.0 * iEvent / nEntries) << "%)" << std::endl;
    }
  }

  std::cout << "\nProcessamento completo!" << std::endl;

  // Fechar arquivo
  file->Close();
  delete file;

  return 0;
}
