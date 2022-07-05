#include <iostream>
#include <cstdlib>
#include <adios2.h>
#include <mpi.h>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <cassert>

void waitForEngineCreation(adios2::IO& io) {
  auto params = io.Parameters();
  bool isStreaming = params.count("Streaming") && (params["Streaming"] == "ON");
  bool timeoutSet = params.count("OpenTimeoutSecs") && std::stoi(params["OpenTimeoutSecs"]) > 0;
  if( isStreaming && timeoutSet ) return;
  std::this_thread::sleep_for(std::chrono::seconds(2));
}

void setupBp4(std::string_view name, adios2::Params params, bool isServer) {
  adios2::ADIOS adios(MPI_COMM_WORLD);
  auto s2cName = std::string(name)+"_s2c"; //s2c = server to client
  auto c2sName = std::string(name)+"_c2s"; //c2s = client to server
  auto s2cIO = adios.DeclareIO(s2cName);
  auto c2sIO = adios.DeclareIO(c2sName);
  s2cIO.SetEngine("BP4");
  c2sIO.SetEngine("BP4");
  s2cIO.SetParameters(params);
  c2sIO.SetParameters(params);
 
  const auto writeEngineName = isServer ? s2cName : c2sName;
  auto writerEngine = isServer ?
                        s2cIO.Open(s2cName, adios2::Mode::Write) :
                        c2sIO.Open(c2sName, adios2::Mode::Write);
  assert(writerEngine);
  waitForEngineCreation(s2cIO);
  waitForEngineCreation(c2sIO);
  auto readerEngine = isServer ?
                        c2sIO.Open(c2sName, adios2::Mode::Read) :
                        s2cIO.Open(s2cName, adios2::Mode::Read);
  assert(readerEngine);

  auto writerStatus = writerEngine.BeginStep();
  assert(writerStatus == adios2::StepStatus::OK);
  writerEngine.EndStep();
  std::cerr << "done writer step\n";

  auto readerStatus = readerEngine.BeginStep();
  assert(readerStatus == adios2::StepStatus::OK);
  readerEngine.EndStep();
  std::cerr << "done reader step\n";

  writerEngine.Close();
  readerEngine.Close();
}

void setupSst(std::string_view name, adios2::Params params, bool isServer) {
  adios2::ADIOS adios(MPI_COMM_WORLD);
  auto s2cName = std::string(name)+"_s2c"; //s2c = server to client
  auto c2sName = std::string(name)+"_c2s"; //c2s = client to server
  auto s2cIO = adios.DeclareIO(s2cName);
  auto c2sIO = adios.DeclareIO(c2sName);
  s2cIO.SetEngine("SST");
  c2sIO.SetEngine("SST");
  s2cIO.SetParameters(params);
  c2sIO.SetParameters(params);

  const auto s2cEngineMode = isServer ? adios2::Mode::Write : adios2::Mode::Read;
  adios2::Engine s2cEngine = s2cIO.Open(s2cName, s2cEngineMode);
  assert(s2cEngine);
  const auto c2sEngineMode = isServer ? adios2::Mode::Read : adios2::Mode::Write;
  adios2::Engine c2sEngine = c2sIO.Open(c2sName, c2sEngineMode);
  assert(c2sEngine);

  auto s2cStatus = s2cEngine.BeginStep();
  assert(s2cStatus == adios2::StepStatus::OK);
  s2cEngine.EndStep();
  std::cerr << "done s2c step\n";

  auto c2sStatus = c2sEngine.BeginStep();
  assert(c2sStatus == adios2::StepStatus::OK);
  c2sEngine.EndStep();
  std::cerr << "done c2s step\n";

  s2cEngine.Close();
  c2sEngine.Close();
}

int main(int argc, char** argv) {
  int rank, nproc;
  MPI_Init(&argc, &argv);
  if(argc > 3) {
    std::cerr << "Usage: " << argv[0] << "<enableSST=0|1> <isServer=0|1>\n";
    exit(EXIT_FAILURE);
  }
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  const auto isSST = (atoi(argv[1]) == 1);
  const auto isServer = atoi(argv[2]);
  fprintf(stderr, "rank %d isServer %d\n", rank, isServer);
  adios2::Params params{ {"Streaming", "ON"}, {"OpenTimeoutSecs", "6"}};
  if(isSST)
    setupSst("client0",params,isServer);
  else
    setupBp4("client0",params,isServer);
  std::cout << "done\n";
  MPI_Finalize();
  return 0;
}
