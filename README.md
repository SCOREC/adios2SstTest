# adios2SstTest
testing server-client communication via adios2 sst

# contents

```
CMakeLists.txt - cmake build system
LICENSE - license
README.md - this file
clientSst_2233781.out - client output with SstVerbose=5
serverSst_2233781.out - server output with SstVerbose=5
envGcc1020.sh - modules loaded on summit
installAdios2SstTest.sh - cmake install commands
runSetupComms.sh - summit lsf job script
setupComms.cpp - test code
```

# build on summit

```
source envGcc1020.sh
./installAdios2SstTest.sh
```

# run on summit

```
bsub ./runSetupComms.sh
```

# output from run with sst

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

