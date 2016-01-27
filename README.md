# PostgreSQL Statistics MIB for Net-SNMP

**pgStatMIB ::= { iso(1) org(3) dod(6) internet(1) private(4) enterprises(1) pgsql(27645) 3 }**

**enterprises.pgsql.pgStatMIB => 1.3.6.1.4.1.27645.3**


## MIB tree designed so far

```
enterprises.pgsql (1.3.6.1.4.1.27645)
|
+--pgStatMIB(3)
   |
   +--pgstatServer(1)
   |  |
   |  +-- -R-- Integer32 pgstatServerDatabaseCount(1)
   |  +-- -R-- Unsigned  pgstatServerSize(2)
   |  +-- -R-- Gauge     pgstatServerBackends(3)
   |  +-- -R-- Counter   pgstatServerCommits(4)
   |  +-- -R-- Counter   pgstatServerRollbacks(5)
   |  +-- -R-- Counter   pgstatServerBlocksRead(6)
   |  +-- -R-- Counter   pgstatServerBlocksHit(7)
   |  +-- -R-- Unsigned  pgstatServerRollbackRatio(8)
   |  |        Range: 0..10000
   |  +-- -R-- Unsigned  pgstatServerCacheHitRatio(9)
   |           Range: 0..10000
   |
   +--pgstatDatabaseTable(2)
   |  |
   |  +--pgstatDatabaseEntry(1)
   |     |  Index: pgstatDatabaseId
   |     |
   |     +-- -R-- Integer32 pgstatDatabaseId(1)
   |     |        Range: 1..2147483647
   |     +-- -R-- String    pgstatDatabaseName(2)
   |     |        Textual Convention: DisplayString
   |     |        Size: 0..64
   |     +-- -R-- Unsigned  pgstatDatabaseSize(3)
   |     +-- -R-- Gauge     pgstatDatabaseBackends(4)
   |     +-- -R-- Counter   pgstatDatabaseCommits(5)
   |     +-- -R-- Counter   pgstatDatabaseRollbacks(6)
   |     +-- -R-- Counter   pgstatDatabaseBlocksRead(7)
   |     +-- -R-- Counter   pgstatDatabaseBlocksHit(8)
   |     +-- -R-- Counter   pgstatDatabaseTuplesReturned(9)
   |     +-- -R-- Counter   pgstatDatabaseTuplesFetched(10)
   |     +-- -R-- Counter   pgstatDatabaseTuplesInserted(11)
   |     +-- -R-- Counter   pgstatDatabaseTuplesUpdated(12)
   |     +-- -R-- Counter   pgstatDatabaseTuplesDeleted(13)
   |     +-- -R-- Unsigned  pgstatDatabaseRollbackRatio(14)
   |     |        Range: 0..10000
   |     +-- -R-- Unsigned  pgstatDatabaseCacheHitRatio(15)
   |     |        Range: 0..10000
   |     +-- -R-- Counter   pgstatDatabaseTuplesModified(16)
   |
   +--pgstatBgWriter(20)
      |
      +-- -R-- Counter   pgstatBgWriterCheckpointsTimed(1)
      +-- -R-- Counter   pgstatBgWriterCheckpointsRequested(2)
      +-- -R-- Counter   pgstatBgWriterBuffersCheckpoint(3)
      +-- -R-- Counter   pgstatBgWriterBuffersClean(4)
      +-- -R-- Counter   pgstatBgWriterMaxWrittenClean(5)
      +-- -R-- Counter   pgstatBgWriterBuffersBackend(6)
      +-- -R-- Counter   pgstatBgWriterBuffersAllocated(7)
```

## Usage samples

### Import MIB definitions for SNMP client

`$ export MIBDIRS="+." MIBS=ALL`

### Get server individual values

`$ snmpget localhost pgstatServerRollbackRatio.0 pgstatServerCacheHitRatio.0`

PGSTAT-MIB::pgstatServerRollbackRatio.0 = Gauge32: 80
PGSTAT-MIB::pgstatServerCacheHitRatio.0 = Gauge32: 9987

### Get all server-wide values

`$ snmpwalk localhost pgstatServer`

PGSTAT-MIB::pgstatServerDatabaseCount.0 = INTEGER: 8
PGSTAT-MIB::pgstatServerSize.0 = Gauge32: 708466976
PGSTAT-MIB::pgstatServerBackends.0 = Gauge32: 2
PGSTAT-MIB::pgstatServerCommits.0 = Counter32: 11460
PGSTAT-MIB::pgstatServerRollbacks.0 = Counter32: 92
PGSTAT-MIB::pgstatServerBlocksRead.0 = Counter32: 41803
PGSTAT-MIB::pgstatServerBlocksHit.0 = Counter32: 32249781
PGSTAT-MIB::pgstatServerRollbackRatio.0 = Gauge32: 80
PGSTAT-MIB::pgstatServerCacheHitRatio.0 = Gauge32: 9987

### Get values from all databases in the server

`$ snmpwalk localhost pgstatDatabase`

PGSTAT-MIB::pgstatDatabaseId.12070 = INTEGER: 12070
PGSTAT-MIB::pgstatDatabaseId.16386 = INTEGER: 16386
PGSTAT-MIB::pgstatDatabaseName.12070 = STRING: postgres
PGSTAT-MIB::pgstatDatabaseName.16386 = STRING: rodrigo
PGSTAT-MIB::pgstatDatabaseSize.12070 = Gauge32: 6219556
PGSTAT-MIB::pgstatDatabaseSize.16386 = Gauge32: 6285092
PGSTAT-MIB::pgstatDatabaseBackends.12070 = Gauge32: 2
PGSTAT-MIB::pgstatDatabaseBackends.16386 = Gauge32: 0
PGSTAT-MIB::pgstatDatabaseCommits.12070 = Counter32: 1070
PGSTAT-MIB::pgstatDatabaseCommits.16386 = Counter32: 1293
PGSTAT-MIB::pgstatDatabaseRollbacks.12070 = Counter32: 3
PGSTAT-MIB::pgstatDatabaseRollbacks.16386 = Counter32: 2
PGSTAT-MIB::pgstatDatabaseBlocksRead.12070 = Counter32: 1068
PGSTAT-MIB::pgstatDatabaseBlocksRead.16386 = Counter32: 880
PGSTAT-MIB::pgstatDatabaseBlocksHit.12070 = Counter32: 48330
PGSTAT-MIB::pgstatDatabaseBlocksHit.16386 = Counter32: 52619
PGSTAT-MIB::pgstatDatabaseTuplesReturned.12070 = Counter32: 430008
PGSTAT-MIB::pgstatDatabaseTuplesReturned.16386 = Counter32: 559879
PGSTAT-MIB::pgstatDatabaseTuplesFetched.12070 = Counter32: 19391
PGSTAT-MIB::pgstatDatabaseTuplesFetched.16386 = Counter32: 18830
PGSTAT-MIB::pgstatDatabaseTuplesInserted.12070 = Counter32: 0
PGSTAT-MIB::pgstatDatabaseTuplesInserted.16386 = Counter32: 0
PGSTAT-MIB::pgstatDatabaseTuplesUpdated.12070 = Counter32: 0
PGSTAT-MIB::pgstatDatabaseTuplesUpdated.16386 = Counter32: 7
PGSTAT-MIB::pgstatDatabaseTuplesDeleted.12070 = Counter32: 0
PGSTAT-MIB::pgstatDatabaseTuplesDeleted.16386 = Counter32: 0
PGSTAT-MIB::pgstatDatabaseRollbackRatio.12070 = Gauge32: 28
PGSTAT-MIB::pgstatDatabaseRollbackRatio.16386 = Gauge32: 15
PGSTAT-MIB::pgstatDatabaseCacheHitRatio.12070 = Gauge32: 9784
PGSTAT-MIB::pgstatDatabaseCacheHitRatio.16386 = Gauge32: 9836
PGSTAT-MIB::pgstatDatabaseTuplesModified.12070 = Counter32: 0
PGSTAT-MIB::pgstatDatabaseTuplesModified.16386 = Counter32: 7

### Get a single value from a specified database (numeric form)

`$ snmpget localhost pgstatDatabaseBackends.12070 -On`

.1.3.6.1.4.1.27645.3.2.1.4.12070 = Gauge32: 2

### Get a single value from a specified database (description form)

`$ snmpget localhost pgstatDatabaseRollbacks.16386 -Of`

.iso.org.dod.internet.private.enterprises.pgsql.pgStatMIB.pgstatDatabaseTable.pgstatDatabaseEntry.pgstatDatabaseRollbacks.16386 = Counter32: 2

### Get multiple values from all databases (tabular form)

`$ snmptable localhost -Cl -CB -Ci -OX -Cb -Cc 16 -Cw 80 pgstatDatabaseTable`

SNMP table: PGSTAT-MIB::pgstatDatabaseTable

Id              Name            Size            Backends        Commits         
Rollbacks       BlocksRead      BlocksHit       TuplesReturned  TuplesFetched   
TuplesInserted  TuplesUpdated   TuplesDeleted   RollbackRatio   CacheHitRatio   
TuplesModified  

index: [12070]
12070           postgres        6219556         2               1070            
3               1068            48330           430008          19391           
0               0               0               28              9784            
0               

index: [16386]
16386           rodrigo         6285092         0               1293            
2               880             52619           559879          18830           
0               7               0               15              9836            
7               

### Get all values from background writer

`$ snmpwalk localhost pgstatBgWriter`

PGSTAT-MIB::pgstatBgWriterCheckpointsTimed.0 = Counter32: 188
PGSTAT-MIB::pgstatBgWriterCheckpointsRequested.0 = Counter32: 8
PGSTAT-MIB::pgstatBgWriterBuffersCheckpoint.0 = Counter32: 40275
PGSTAT-MIB::pgstatBgWriterBuffersClean.0 = Counter32: 0
PGSTAT-MIB::pgstatBgWriterMaxWrittenClean.0 = Counter32: 0
PGSTAT-MIB::pgstatBgWriterBuffersBackend.0 = Counter32: 38153
PGSTAT-MIB::pgstatBgWriterBuffersAllocated.0 = Counter32: 43407

### Get a single value from background writer (exact form)

`$ snmpget localhost pgstatBgWriterCheckpointsRequested.0`

PGSTAT-MIB::pgstatBgWriterCheckpointsRequested.0 = Counter32: 8

### Get a single value from background writer (approximate form)

`$ snmpgetnext localhost pgstatBgWriterBuffersCheckpoint`

PGSTAT-MIB::pgstatBgWriterBuffersCheckpoint.0 = Counter32: 40275

## Status of expected sub-trees

- pgstatServer: DONE!

- pgstatDatabases: still need data caching

- pgstatAllTables
- pgstatSysTables
- pgstatUsrTables: specified

- pgstatIOAllTables
- pgstatIOSysTables
- pgstatIOUsrTables

- pgstatAllIndexes
- pgstatSysIndexes
- pgstatUsrIndexes: specified

- pgstatIOAllIndexes
- pgstatIOSysIndexes
- pgstatIOUsrIndexes

- pgstatIOAllSequences
- pgstatIOSysSequences
- pgstatIOUsrSequences

- pgstatActivity
- pgstatBgWriter: DONE!

- pgstatDatabaseConflicts
- pgstatReplication

- pgstatUserFunctions

