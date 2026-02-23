#!/bin/bash
DIR_OUTPUT="/media/danbiajujumiguel/T7/ttbar_BH_analysis/output/"
DIR_SOURCE="/media/danbiajujumiguel/T7/ttbar_BH_analysis/source/"
DIR_INPUT="/media/danbiajujumiguel/T7/ttbar_BH_analysis/input_root/"

${DIR_SOURCE}top_inclusive_withBH_overlay ${DIR_INPUT}pqcd_LO_100tev_5M_converted.root ${DIR_OUTPUT}analysis_pqcd_LO_100tev_5M_converted.root 1.88467E+04
${DIR_SOURCE}top_inclusive_withBH_overlay ${DIR_INPUT}pqcd_NLO_100tev_5M_converted.root ${DIR_OUTPUT}analysis_pqcd_NLO_100tev_5M_converted.root 2.81E+04
${DIR_SOURCE}top_inclusive_withBH_overlay ${DIR_INPUT}100tev_n6_md4_mbh8_converted.root ${DIR_OUTPUT}analysis_100tev_n6_md4_mbh8_converted.root 6.7979721e+02
