# BeamTestEpicTof
EIC Online Reconstruction for BeamTest

==== How to run ====
```
./eic-shell
source /opt/detector/epic-main/bin/thisepic.sh
source envSet.sh
source compile.sh
eicrecon ../../inputFiles/TOFBarrelADCTDC_1_2_3.root   -Pjana:plugin_path=/home/tkumaoka/eic/BeamTest/BeamTestEpicTof/TofClustering/install/lib   -Pplugins=LGADBeamTestPlugin   -Ppodio:output_collections="KumaTOFBarrelCalibratedHits1,KumaTOFBarrelCalibratedHits2,KumaTOFBarrelCalibratedHits3,KumaTOFBarrelClusterHits1,KumaTOFBarrelClusterHits2,KumaTOFBarrelClusterHits3,KumaTOFTracks"   -Pdd4hep:xml_files=geometry/btTOF.xml -Ppodio:output_file=output/oEicrecon.root  -Pjana:nevents=5
```
