# adios2SstTest
testing server-client communication via adios2 sst

The Summit runs use the ADIOS2 system install, version 2.7.1, and the SCOREC RHEL7
runs use version 2.8.0.84.

The same non-fatal ADIOS2 output is produced on both systems, `Got an unexpected
connection close event`.  The full output is pasted below.

# contents

```
setupComms.cpp - test code
CMakeLists.txt - cmake build system
LICENSE - license
README.md - this file
clientSst_2233781.out - client output with SstVerbose=5 on summit
serverSst_2233781.out - server output with SstVerbose=5 on summit
envGcc1020.sh - modules loaded on summit
installAdios2SstTest.sh - cmake install commands on summit
runSetupComms.sh - summit lsf job script
envGcc1010_scorecRhel7.sh - modules loaded on scorec rhel7
installAdios2SstTest_scorecRhel7.sh - cmake install commands on scorec rhel7
runSetupComms_scorecRhel7.sh - bash run script on scorec rhel7
clientSst_scorecRhel7.out - client output with SstVerbose=5 on scorec rhel7
serverSst_scorecRhel7.out - server output with SstVerbose=5 on scorec rhel7
```

## Summit

### build

```
source envGcc1020.sh
./installAdios2SstTest.sh
```

### run

```
bsub ./runSetupComms.sh
```

### output from run with sst

There are non-fatal errors in the SST output that do not appear in the BP4
output.

See the included `serverSst_2233781.out` and `clientSst_2233781.out` for the
output with `SstVerbose=5`.

```
$ cat serverSst_2233751.out
rank 0 isServer 1
done s2c step
Writer 0 (0x3a15a180): Reader 0 (0x3a55d970): Message failed to send to writer 0
(0x18eef7c0)
done c2s step
Got an unexpected connection close event
SST stream open at exit, unlinking contact file (
done

$ cat clientSst_2233751.out
rank 0 isServer 0
done s2c step
done c2s step
SST stream open at exit, unlinking contact file
/gpfs/alpine/fus123/scratch/cwsmith/twoClientWdmCplTesting/client0_c2s.sst
done
```

# output from run with bp4

```
$ cat serverBp4_2233751.out 
rank 0 isServer 1
done writer step
done reader step
done

$ cat clientBp4_2233751.out 
rank 0 isServer 0
done writer step
done reader step
done
```

## SCOREC RHEL7

### build

```
source envGcc1010_scorecRhel7.sh
./installAdios2SstTest_scorecRhel7.sh
```

### run

```
./runSetupComms_scorecRhel7.sh
```

### output from run with sst


See the included `[client|server]Sst_scorecRhel7.out` for the
output with `SstVerbose=5`.

```
$ cat serverSst.out 
rank 0 isServer 1
done s2c step
Writer 0 (0x12ff8a0): Got an unexpected connection close event
done c2s step
done
SST stream open at exit, unlinking contact file

$ cat clientSst.out
rank 0 isServer 0
done s2c step
done c2s step
done
SST stream open at exit, unlinking contact file p
```


### output from run with bp4

```
$ cat clientBp4.out 
rank 0 isServer 0
done writer step
done reader step
done

$ cat serverBp4.out 
rank 0 isServer 1
done writer step
done reader step
done
```
