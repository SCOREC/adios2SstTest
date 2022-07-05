#!/bin/sh
# vim: set tw=120:

run() {
  local processes=$1
  local exe=$2
  local args=$3
  local outfile=$4
  local isSstVerbose=$5

  if [ ${isSstVerbose} == 1 ]; then
    export SstVerbose=5
  fi
  echo "rdmaVars $rdmaVars"

  set -x
  mpirun -np ${processes} ${exe} ${args} &>> ${outfile} &
  set +x
}

rmOutputFiles() {
  rm *.out
}

rmAdiosFiles() {
  rm -rf *.bp
  rm -rf *.sst
}

rmAdiosFiles
rmOutputFiles

bin=/space/cwsmith/wdmCpl/buildAdios2SstTest/setupComms

serverRanks=1
serverNodes=1

clientRanks=1
clientNodes=1

isSst=1
isSstVerbose=0

clientExe=${bin}
clientArgs="${isSst} 0"
clientOut=clientSst.out
run $clientRanks $clientExe "$clientArgs" $clientOut ${isSstVerbose}

serverExe=${bin}
serverArgs="${isSst} 1"
serverOut=serverSst.out
run $serverRanks $serverExe "$serverArgs" $serverOut ${isSstVerbose}

set -x    
wait
rmAdiosFiles
set +x

isSst=0
isSstVerbose=0

clientExe=${bin}
clientArgs="${isSst} 0"
clientOut=clientBp4.out
run $clientRanks $clientExe "$clientArgs" $clientOut ${isSstVerbose}

serverExe=${bin}
serverArgs="${isSst} 1"
serverOut=serverBp4.out
run $serverRanks $serverExe "$serverArgs" $serverOut ${isSstVerbose}

set -x    
wait
rmAdiosFiles
set +x
