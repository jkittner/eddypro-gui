/***************************************************************************
  ecinidefs.h
  -------------------
  Copyright (C) 2007-2011, Eco2s team, Antonio Forgione
  Copyright (C) 2011-2015, LI-COR Biosciences
  Author: Antonio Forgione

  This file is part of EddyPro (R).

  EddyPro (R) is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  EddyPro (R) is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with EddyPro (R). If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#ifndef ECINIDEFS_H
#define ECINIDEFS_H

class QString;

namespace EcIni
{
    // processing file ini keys
    const QString INIGROUP_PROJECT = QStringLiteral("Project");
    const QString INI_PROJECT_0    = QStringLiteral("creation_date");
    const QString INI_PROJECT_1    = QStringLiteral("last_change_date");
    const QString INI_PROJECT_2    = QStringLiteral("file_name");
    const QString INI_PROJECT_3    = QStringLiteral("project_title");
    const QString INI_PROJECT_4    = QStringLiteral("sw_version");
    const QString INI_PROJECT_5    = QStringLiteral("ini_version");
    const QString INI_PROJECT_6    = QStringLiteral("project_id");
    const QString INI_PROJECT_7    = QStringLiteral("file_type");
    const QString INI_PROJECT_8    = QStringLiteral("file_prototype");
    const QString INI_PROJECT_9    = QStringLiteral("use_pfile");
    const QString INI_PROJECT_10   = QStringLiteral("proj_file");
    const QString INI_PROJECT_11   = QStringLiteral("use_dyn_md_file");
    const QString INI_PROJECT_12   = QStringLiteral("dyn_metadata_file");
    const QString INI_PROJECT_13   = QStringLiteral("binary_hnlines");
    const QString INI_PROJECT_14   = QStringLiteral("binary_eol");
    const QString INI_PROJECT_15   = QStringLiteral("binary_nbytes");
    const QString INI_PROJECT_16   = QStringLiteral("binary_little_end");
    const QString INI_PROJECT_17   = QStringLiteral("master_sonic");
    const QString INI_PROJECT_18   = QStringLiteral("col_co2");
    const QString INI_PROJECT_19   = QStringLiteral("col_h2o");
    const QString INI_PROJECT_20   = QStringLiteral("col_ch4");
    const QString INI_PROJECT_21   = QStringLiteral("col_n2o");
    const QString INI_PROJECT_22   = QStringLiteral("col_int_t_1");
    const QString INI_PROJECT_23   = QStringLiteral("col_int_t_2");
    const QString INI_PROJECT_24   = QStringLiteral("col_int_p");
    const QString INI_PROJECT_25   = QStringLiteral("col_air_t");
    const QString INI_PROJECT_26   = QStringLiteral("col_air_p");
    const QString INI_PROJECT_27   = QStringLiteral("col_cell_t");
    const QString INI_PROJECT_28   = QStringLiteral("col_diag_75");
    const QString INI_PROJECT_29   = QStringLiteral("col_diag_72");
    const QString INI_PROJECT_30   = QStringLiteral("col_diag_77");
    const QString INI_PROJECT_31   = QStringLiteral("gas_mw");
    const QString INI_PROJECT_32   = QStringLiteral("gas_diff");
    const QString INI_PROJECT_33_OLD = QStringLiteral("is_express");
    const QString INI_PROJECT_33   = QStringLiteral("run_mode");
    const QString INI_PROJECT_34   = QStringLiteral("use_biom");
    const QString INI_PROJECT_35   = QStringLiteral("biom_file");
    const QString INI_PROJECT_36   = QStringLiteral("col_ts");
    const QString INI_PROJECT_37   = QStringLiteral("out_ghg_eu");
    const QString INI_PROJECT_38   = QStringLiteral("out_amflux");
    const QString INI_PROJECT_39   = QStringLiteral("out_rich");
    const QString INI_PROJECT_40   = QStringLiteral("run_fcc");
    const QString INI_PROJECT_41   = QStringLiteral("make_dataset");
    const QString INI_PROJECT_42   = QStringLiteral("pr_start_date");
    const QString INI_PROJECT_43   = QStringLiteral("pr_end_date");
    const QString INI_PROJECT_44   = QStringLiteral("pr_start_time");
    const QString INI_PROJECT_45   = QStringLiteral("pr_end_time");
    const QString INI_PROJECT_46   = QStringLiteral("hf_meth");
    const QString INI_PROJECT_47   = QStringLiteral("lf_meth");
    const QString INI_PROJECT_48   = QStringLiteral("wpl_meth");
    const QString INI_PROJECT_49   = QStringLiteral("foot_meth");
    const QString INI_PROJECT_50   = QStringLiteral("tob1_format");
    const QString INI_PROJECT_51   = QStringLiteral("out_path");
    const QString INI_PROJECT_52   = QStringLiteral("fix_out_format");
    const QString INI_PROJECT_53   = QStringLiteral("err_label");
    const QString INI_PROJECT_54   = QStringLiteral("pr_subset");
    const QString INI_PROJECT_55   = QStringLiteral("qc_meth");
    const QString INI_PROJECT_56   = QStringLiteral("out_metadata");
    const QString INI_PROJECT_57   = QStringLiteral("biom_dir");
    const QString INI_PROJECT_58   = QStringLiteral("biom_rec");
    const QString INI_PROJECT_59   = QStringLiteral("biom_ext");
    const QString INI_PROJECT_60   = QStringLiteral("out_mean_cosp");
    const QString INI_PROJECT_61   = QStringLiteral("out_biomet");
    const QString INI_PROJECT_62   = QStringLiteral("bin_sp_avail");
    const QString INI_PROJECT_63   = QStringLiteral("full_sp_avail");
    const QString INI_PROJECT_64   = QStringLiteral("files_found");

    const QString INIGROUP_SPEC_SETTINGS = QStringLiteral("FluxCorrection_SpectralAnalysis_General");
    const QString INI_SPEC_SETTINGS_0    = QStringLiteral("sa_start_date");
    const QString INI_SPEC_SETTINGS_1    = QStringLiteral("sa_end_date");
    const QString INI_SPEC_SETTINGS_2    = QStringLiteral("sa_mode");
    const QString INI_SPEC_SETTINGS_3    = QStringLiteral("sa_file");
    const QString INI_SPEC_SETTINGS_4    = QStringLiteral("sa_min_smpl");
    const QString INI_SPEC_SETTINGS_5    = QStringLiteral("sa_fmin_co2");
    const QString INI_SPEC_SETTINGS_6    = QStringLiteral("sa_fmin_h2o");
    const QString INI_SPEC_SETTINGS_7    = QStringLiteral("sa_fmin_ch4");
    const QString INI_SPEC_SETTINGS_8    = QStringLiteral("sa_fmin_gas4");
    const QString INI_SPEC_SETTINGS_9    = QStringLiteral("sa_fmax_co2");
    const QString INI_SPEC_SETTINGS_10   = QStringLiteral("sa_fmax_h2o");
    const QString INI_SPEC_SETTINGS_11   = QStringLiteral("sa_fmax_ch4");
    const QString INI_SPEC_SETTINGS_12   = QStringLiteral("sa_fmax_gas4");
    const QString INI_SPEC_SETTINGS_13   = QStringLiteral("sa_hfn_co2_fmin");
    const QString INI_SPEC_SETTINGS_14   = QStringLiteral("sa_hfn_h2o_fmin");
    const QString INI_SPEC_SETTINGS_15   = QStringLiteral("sa_hfn_ch4_fmin");
    const QString INI_SPEC_SETTINGS_16   = QStringLiteral("sa_hfn_gas4_fmin");
    const QString INI_SPEC_SETTINGS_17   = QStringLiteral("sa_min_co2");
    const QString INI_SPEC_SETTINGS_18   = QStringLiteral("sa_min_ch4");
    const QString INI_SPEC_SETTINGS_19   = QStringLiteral("sa_min_gas4");
    const QString INI_SPEC_SETTINGS_20   = QStringLiteral("sa_min_le");
    const QString INI_SPEC_SETTINGS_21   = QStringLiteral("sa_min_h");
    const QString INI_SPEC_SETTINGS_22   = QStringLiteral("add_sonic_lptf");
    const QString INI_SPEC_SETTINGS_23   = QStringLiteral("f10_co2_trshld");
    const QString INI_SPEC_SETTINGS_24   = QStringLiteral("f10_ch4_trshld");
    const QString INI_SPEC_SETTINGS_25   = QStringLiteral("f10_gas4_trshld");
    const QString INI_SPEC_SETTINGS_26   = QStringLiteral("f10_le_trshld");
    const QString INI_SPEC_SETTINGS_27   = QStringLiteral("f10_h_trshld");
    const QString INI_SPEC_SETTINGS_28   = QStringLiteral("horst_lens");
    const QString INI_SPEC_SETTINGS_29   = QStringLiteral("ex_file");
    const QString INI_SPEC_SETTINGS_30   = QStringLiteral("sa_bin_spectra");
    const QString INI_SPEC_SETTINGS_31   = QStringLiteral("sa_full_spectra");
    const QString INI_SPEC_SETTINGS_32   = QStringLiteral("ex_dir");
    const QString INI_SPEC_SETTINGS_33   = QStringLiteral("sa_subset");

    const QString INIGROUP_SCREEN_GENERAL = QStringLiteral("RawProcess_General");
    const QString INI_SCREEN_GENERAL_4    = QStringLiteral("data_path");
    const QString INI_SCREEN_GENERAL_6    = QStringLiteral("recurse");
    const QString INI_SCREEN_GENERAL_8    = QStringLiteral("flag1_column");
    const QString INI_SCREEN_GENERAL_9    = QStringLiteral("flag1_threshold");
    const QString INI_SCREEN_GENERAL_10   = QStringLiteral("flag1_upper");
    const QString INI_SCREEN_GENERAL_11   = QStringLiteral("flag2_column");
    const QString INI_SCREEN_GENERAL_12   = QStringLiteral("flag2_threshold");
    const QString INI_SCREEN_GENERAL_13   = QStringLiteral("flag2_upper");
    const QString INI_SCREEN_GENERAL_14   = QStringLiteral("flag3_column");
    const QString INI_SCREEN_GENERAL_15   = QStringLiteral("flag3_threshold");
    const QString INI_SCREEN_GENERAL_16   = QStringLiteral("flag3_upper");
    const QString INI_SCREEN_GENERAL_17   = QStringLiteral("flag4_column");
    const QString INI_SCREEN_GENERAL_18   = QStringLiteral("flag4_threshold");
    const QString INI_SCREEN_GENERAL_19   = QStringLiteral("flag4_upper");
    const QString INI_SCREEN_GENERAL_20   = QStringLiteral("flag5_column");
    const QString INI_SCREEN_GENERAL_21   = QStringLiteral("flag5_threshold");
    const QString INI_SCREEN_GENERAL_22   = QStringLiteral("flag5_upper");
    const QString INI_SCREEN_GENERAL_23   = QStringLiteral("flag6_column");
    const QString INI_SCREEN_GENERAL_24   = QStringLiteral("flag6_threshold");
    const QString INI_SCREEN_GENERAL_25   = QStringLiteral("flag6_upper");
    const QString INI_SCREEN_GENERAL_26   = QStringLiteral("flag7_column");
    const QString INI_SCREEN_GENERAL_27   = QStringLiteral("flag7_threshold");
    const QString INI_SCREEN_GENERAL_28   = QStringLiteral("flag7_upper");
    const QString INI_SCREEN_GENERAL_29   = QStringLiteral("flag8_column");
    const QString INI_SCREEN_GENERAL_30   = QStringLiteral("flag8_threshold");
    const QString INI_SCREEN_GENERAL_31   = QStringLiteral("flag8_upper");
    const QString INI_SCREEN_GENERAL_32   = QStringLiteral("flag9_column");
    const QString INI_SCREEN_GENERAL_33   = QStringLiteral("flag9_threshold");
    const QString INI_SCREEN_GENERAL_34   = QStringLiteral("flag9_upper");
    const QString INI_SCREEN_GENERAL_35   = QStringLiteral("flag10_column");
    const QString INI_SCREEN_GENERAL_36   = QStringLiteral("flag10_threshold");
    const QString INI_SCREEN_GENERAL_37   = QStringLiteral("flag10_upper");
    const QString INI_SCREEN_GENERAL_38   = QStringLiteral("mag_dec");
    const QString INI_SCREEN_GENERAL_39   = QStringLiteral("dec_date");
    const QString INI_SCREEN_GENERAL_40   = QStringLiteral("use_geo_north");

    const QString INIGROUP_SCREEN_SETTINGS = QStringLiteral("RawProcess_Settings");
    const QString INI_SCREEN_SETTINGS_0    = QStringLiteral("nfiles");
    const QString INI_SCREEN_SETTINGS_1    = QStringLiteral("max_lack");
    const QString INI_SCREEN_SETTINGS_2    = QStringLiteral("cross_wind");
    const QString INI_SCREEN_SETTINGS_3    = QStringLiteral("flow_distortion");
    const QString INI_SCREEN_SETTINGS_4    = QStringLiteral("rot_meth");
    const QString INI_SCREEN_SETTINGS_5    = QStringLiteral("detrend_meth");
    const QString INI_SCREEN_SETTINGS_6    = QStringLiteral("timeconst");
    const QString INI_SCREEN_SETTINGS_7    = QStringLiteral("tlag_meth");
    const QString INI_SCREEN_SETTINGS_8    = QStringLiteral("tap_win");
    const QString INI_SCREEN_SETTINGS_9    = QStringLiteral("nbins");
    const QString INI_SCREEN_SETTINGS_10   = QStringLiteral("avrg_len");
    const QString INI_SCREEN_SETTINGS_12   = QStringLiteral("u_offset");
    const QString INI_SCREEN_SETTINGS_13   = QStringLiteral("v_offset");
    const QString INI_SCREEN_SETTINGS_14   = QStringLiteral("w_offset");
    const QString INI_SCREEN_SETTINGS_15   = QStringLiteral("out_bin_sp");
    const QString INI_SCREEN_SETTINGS_16   = QStringLiteral("out_full_sp_u");
    const QString INI_SCREEN_SETTINGS_17   = QStringLiteral("out_full_sp_v");
    const QString INI_SCREEN_SETTINGS_18   = QStringLiteral("out_full_sp_w");
    const QString INI_SCREEN_SETTINGS_19   = QStringLiteral("out_full_sp_ts");
    const QString INI_SCREEN_SETTINGS_20   = QStringLiteral("out_full_sp_co2");
    const QString INI_SCREEN_SETTINGS_21   = QStringLiteral("out_full_sp_h2o");
    const QString INI_SCREEN_SETTINGS_22   = QStringLiteral("out_full_sp_ch4");
    const QString INI_SCREEN_SETTINGS_23   = QStringLiteral("out_full_sp_n2o");
    const QString INI_SCREEN_SETTINGS_24   = QStringLiteral("out_st_1");
    const QString INI_SCREEN_SETTINGS_25   = QStringLiteral("out_st_2");
    const QString INI_SCREEN_SETTINGS_26   = QStringLiteral("out_st_3");
    const QString INI_SCREEN_SETTINGS_27   = QStringLiteral("out_st_4");
    const QString INI_SCREEN_SETTINGS_28   = QStringLiteral("out_st_5");
    const QString INI_SCREEN_SETTINGS_29   = QStringLiteral("out_st_6");
    const QString INI_SCREEN_SETTINGS_30   = QStringLiteral("out_st_7");
    const QString INI_SCREEN_SETTINGS_31   = QStringLiteral("out_full_cosp_w_u");
    const QString INI_SCREEN_SETTINGS_32   = QStringLiteral("out_full_cosp_w_v");
    const QString INI_SCREEN_SETTINGS_33   = QStringLiteral("out_full_cosp_w_ts");
    const QString INI_SCREEN_SETTINGS_34   = QStringLiteral("out_full_cosp_w_co2");
    const QString INI_SCREEN_SETTINGS_35   = QStringLiteral("out_full_cosp_w_h2o");
    const QString INI_SCREEN_SETTINGS_36   = QStringLiteral("out_full_cosp_w_ch4");
    const QString INI_SCREEN_SETTINGS_37   = QStringLiteral("out_full_cosp_w_n2o");
    const QString INI_SCREEN_SETTINGS_38   = QStringLiteral("out_bin_og");
    const QString INI_SCREEN_SETTINGS_39   = QStringLiteral("to_mixratio");
    const QString INI_SCREEN_SETTINGS_40   = QStringLiteral("filter_sr");
    const QString INI_SCREEN_SETTINGS_41   = QStringLiteral("filter_al");
    const QString INI_SCREEN_SETTINGS_44   = QStringLiteral("bu_corr");
    const QString INI_SCREEN_SETTINGS_45   = QStringLiteral("bu_multi");
    const QString INI_SCREEN_SETTINGS_46   = QStringLiteral("l_day_bot_gain");
    const QString INI_SCREEN_SETTINGS_47   = QStringLiteral("l_day_bot_offset");
    const QString INI_SCREEN_SETTINGS_48   = QStringLiteral("l_day_top_gain");
    const QString INI_SCREEN_SETTINGS_49   = QStringLiteral("l_day_top_offset");
    const QString INI_SCREEN_SETTINGS_50   = QStringLiteral("l_day_spar_gain");
    const QString INI_SCREEN_SETTINGS_51   = QStringLiteral("l_day_spar_offset");
    const QString INI_SCREEN_SETTINGS_52   = QStringLiteral("l_night_bot_gain");
    const QString INI_SCREEN_SETTINGS_53   = QStringLiteral("l_night_bot_offset");
    const QString INI_SCREEN_SETTINGS_54   = QStringLiteral("l_night_top_gain");
    const QString INI_SCREEN_SETTINGS_55   = QStringLiteral("l_night_top_offset");
    const QString INI_SCREEN_SETTINGS_56   = QStringLiteral("l_night_spar_gain");
    const QString INI_SCREEN_SETTINGS_57   = QStringLiteral("l_night_spar_offset");
    const QString INI_SCREEN_SETTINGS_58   = QStringLiteral("m_day_bot1");
    const QString INI_SCREEN_SETTINGS_59   = QStringLiteral("m_day_bot2");
    const QString INI_SCREEN_SETTINGS_60   = QStringLiteral("m_day_bot3");
    const QString INI_SCREEN_SETTINGS_61   = QStringLiteral("m_day_bot4");
    const QString INI_SCREEN_SETTINGS_62   = QStringLiteral("m_day_top1");
    const QString INI_SCREEN_SETTINGS_63   = QStringLiteral("m_day_top2");
    const QString INI_SCREEN_SETTINGS_64   = QStringLiteral("m_day_top3");
    const QString INI_SCREEN_SETTINGS_65   = QStringLiteral("m_day_top4");
    const QString INI_SCREEN_SETTINGS_66   = QStringLiteral("m_day_spar1");
    const QString INI_SCREEN_SETTINGS_67   = QStringLiteral("m_day_spar2");
    const QString INI_SCREEN_SETTINGS_68   = QStringLiteral("m_day_spar3");
    const QString INI_SCREEN_SETTINGS_69   = QStringLiteral("m_day_spar4");
    const QString INI_SCREEN_SETTINGS_70   = QStringLiteral("m_night_bot1");
    const QString INI_SCREEN_SETTINGS_71   = QStringLiteral("m_night_bot2");
    const QString INI_SCREEN_SETTINGS_72   = QStringLiteral("m_night_bot3");
    const QString INI_SCREEN_SETTINGS_73   = QStringLiteral("m_night_bot4");
    const QString INI_SCREEN_SETTINGS_74   = QStringLiteral("m_night_top1");
    const QString INI_SCREEN_SETTINGS_75   = QStringLiteral("m_night_top2");
    const QString INI_SCREEN_SETTINGS_76   = QStringLiteral("m_night_top3");
    const QString INI_SCREEN_SETTINGS_77   = QStringLiteral("m_night_top4");
    const QString INI_SCREEN_SETTINGS_78   = QStringLiteral("m_night_spar1");
    const QString INI_SCREEN_SETTINGS_79   = QStringLiteral("m_night_spar2");
    const QString INI_SCREEN_SETTINGS_80   = QStringLiteral("m_night_spar3");
    const QString INI_SCREEN_SETTINGS_81   = QStringLiteral("m_night_spar4");
    const QString INI_SCREEN_SETTINGS_82   = QStringLiteral("out_raw_1");
    const QString INI_SCREEN_SETTINGS_83   = QStringLiteral("out_raw_2");
    const QString INI_SCREEN_SETTINGS_84   = QStringLiteral("out_raw_3");
    const QString INI_SCREEN_SETTINGS_85   = QStringLiteral("out_raw_4");
    const QString INI_SCREEN_SETTINGS_86   = QStringLiteral("out_raw_5");
    const QString INI_SCREEN_SETTINGS_87   = QStringLiteral("out_raw_6");
    const QString INI_SCREEN_SETTINGS_88   = QStringLiteral("out_raw_7");
    const QString INI_SCREEN_SETTINGS_89   = QStringLiteral("out_raw_u");
    const QString INI_SCREEN_SETTINGS_90   = QStringLiteral("out_raw_v");
    const QString INI_SCREEN_SETTINGS_91   = QStringLiteral("out_raw_w");
    const QString INI_SCREEN_SETTINGS_92   = QStringLiteral("out_raw_ts");
    const QString INI_SCREEN_SETTINGS_93   = QStringLiteral("out_raw_co2");
    const QString INI_SCREEN_SETTINGS_94   = QStringLiteral("out_raw_h2o");
    const QString INI_SCREEN_SETTINGS_95   = QStringLiteral("out_raw_ch4");
    const QString INI_SCREEN_SETTINGS_96   = QStringLiteral("out_raw_gas4");
    const QString INI_SCREEN_SETTINGS_97   = QStringLiteral("out_raw_t_air");
    const QString INI_SCREEN_SETTINGS_98   = QStringLiteral("out_raw_p_air");
    const QString INI_SCREEN_SETTINGS_99   = QStringLiteral("out_qc_details");
    const QString INI_SCREEN_SETTINGS_101  = QStringLiteral("power_of_two");

    const QString INIGROUP_SCREEN_TESTS = QStringLiteral("RawProcess_Tests");
    const QString INI_SCREEN_TESTS_0    = QStringLiteral("test_sr");
    const QString INI_SCREEN_TESTS_1    = QStringLiteral("test_ar");
    const QString INI_SCREEN_TESTS_2    = QStringLiteral("test_do");
    const QString INI_SCREEN_TESTS_3    = QStringLiteral("test_al");
    const QString INI_SCREEN_TESTS_4    = QStringLiteral("test_sk");
    const QString INI_SCREEN_TESTS_5    = QStringLiteral("test_ds");
    const QString INI_SCREEN_TESTS_6    = QStringLiteral("test_tl");
    const QString INI_SCREEN_TESTS_7    = QStringLiteral("test_aa");
    const QString INI_SCREEN_TESTS_8    = QStringLiteral("test_ns");

    const QString INIGROUP_SCREEN_PARAM = QStringLiteral("RawProcess_ParameterSettings");
    const QString INI_SCREEN_PARAM_0    = QStringLiteral("sr_num_spk");
    const QString INI_SCREEN_PARAM_1    = QStringLiteral("sr_lim_u");
    const QString INI_SCREEN_PARAM_2    = QStringLiteral("sr_lim_hf");
    const QString INI_SCREEN_PARAM_3    = QStringLiteral("ar_lim");
    const QString INI_SCREEN_PARAM_4    = QStringLiteral("ar_bins");
    const QString INI_SCREEN_PARAM_5    = QStringLiteral("ar_hf_lim");
    const QString INI_SCREEN_PARAM_6    = QStringLiteral("do_extlim_dw");
    const QString INI_SCREEN_PARAM_7    = QStringLiteral("do_hf1_lim");
    const QString INI_SCREEN_PARAM_8    = QStringLiteral("do_hf2_lim");
    const QString INI_SCREEN_PARAM_9    = QStringLiteral("al_u_max");
    const QString INI_SCREEN_PARAM_10   = QStringLiteral("al_w_max");
    const QString INI_SCREEN_PARAM_11   = QStringLiteral("al_tson_min");
    const QString INI_SCREEN_PARAM_12   = QStringLiteral("al_tson_max");
    const QString INI_SCREEN_PARAM_13   = QStringLiteral("al_co2_min");
    const QString INI_SCREEN_PARAM_14   = QStringLiteral("al_co2_max");
    const QString INI_SCREEN_PARAM_15   = QStringLiteral("al_h2o_min");
    const QString INI_SCREEN_PARAM_16   = QStringLiteral("al_h2o_max");
    const QString INI_SCREEN_PARAM_17   = QStringLiteral("sk_hf_skmin");
    const QString INI_SCREEN_PARAM_18   = QStringLiteral("sk_hf_skmax");
    const QString INI_SCREEN_PARAM_19   = QStringLiteral("sk_sf_skmin");
    const QString INI_SCREEN_PARAM_20   = QStringLiteral("sk_sf_skmax");
    const QString INI_SCREEN_PARAM_21   = QStringLiteral("sk_hf_kumin");
    const QString INI_SCREEN_PARAM_22   = QStringLiteral("sk_hf_kumax");
    const QString INI_SCREEN_PARAM_23   = QStringLiteral("sk_sf_kumin");
    const QString INI_SCREEN_PARAM_24   = QStringLiteral("sk_sf_kumax");
    const QString INI_SCREEN_PARAM_25   = QStringLiteral("ds_hf_uv");
    const QString INI_SCREEN_PARAM_26   = QStringLiteral("ds_hf_w");
    const QString INI_SCREEN_PARAM_27   = QStringLiteral("ds_hf_t");
    const QString INI_SCREEN_PARAM_28   = QStringLiteral("ds_hf_co2");
    const QString INI_SCREEN_PARAM_29   = QStringLiteral("ds_hf_h2o");
    const QString INI_SCREEN_PARAM_30   = QStringLiteral("ds_hf_var");
    const QString INI_SCREEN_PARAM_31   = QStringLiteral("ds_sf_uv");
    const QString INI_SCREEN_PARAM_32   = QStringLiteral("ds_sf_w");
    const QString INI_SCREEN_PARAM_33   = QStringLiteral("ds_sf_t");
    const QString INI_SCREEN_PARAM_34   = QStringLiteral("ds_sf_co2");
    const QString INI_SCREEN_PARAM_35   = QStringLiteral("ds_sf_h2o");
    const QString INI_SCREEN_PARAM_36   = QStringLiteral("ds_sf_var");
    const QString INI_SCREEN_PARAM_37   = QStringLiteral("tl_hf_lim");
    const QString INI_SCREEN_PARAM_38   = QStringLiteral("tl_sf_lim");
    const QString INI_SCREEN_PARAM_39   = QStringLiteral("tl_def_co2");
    const QString INI_SCREEN_PARAM_40   = QStringLiteral("tl_def_h2o");
    const QString INI_SCREEN_PARAM_41   = QStringLiteral("aa_min");
    const QString INI_SCREEN_PARAM_42   = QStringLiteral("aa_max");
    const QString INI_SCREEN_PARAM_43   = QStringLiteral("aa_lim");
    const QString INI_SCREEN_PARAM_44   = QStringLiteral("ns_hf_lim");
    const QString INI_SCREEN_PARAM_45   = QStringLiteral("sr_lim_w");
    const QString INI_SCREEN_PARAM_46   = QStringLiteral("sr_lim_co2");
    const QString INI_SCREEN_PARAM_47   = QStringLiteral("sr_lim_h2o");
    const QString INI_SCREEN_PARAM_48   = QStringLiteral("sr_lim_ch4");
    const QString INI_SCREEN_PARAM_49   = QStringLiteral("sr_lim_n2o");
    const QString INI_SCREEN_PARAM_50   = QStringLiteral("ds_hf_ch4");
    const QString INI_SCREEN_PARAM_51   = QStringLiteral("ds_hf_n2o");
    const QString INI_SCREEN_PARAM_52   = QStringLiteral("ds_sf_ch4");
    const QString INI_SCREEN_PARAM_53   = QStringLiteral("ds_sf_n2o");
    const QString INI_SCREEN_PARAM_54   = QStringLiteral("al_ch4_min");
    const QString INI_SCREEN_PARAM_55   = QStringLiteral("al_ch4_max");
    const QString INI_SCREEN_PARAM_56   = QStringLiteral("al_n2o_min");
    const QString INI_SCREEN_PARAM_57   = QStringLiteral("al_n2o_max");
    const QString INI_SCREEN_PARAM_58   = QStringLiteral("tl_def_ch4");
    const QString INI_SCREEN_PARAM_59   = QStringLiteral("tl_def_n2o");

    const QString INIGROUP_SCREEN_TILT   = QStringLiteral("RawProcess_TiltCorrection_Settings");
    const QString INI_SCREEN_TILT_0      = QStringLiteral("pf_start_date");
    const QString INI_SCREEN_TILT_1      = QStringLiteral("pf_end_date");
    const QString INI_SCREEN_TILT_2      = QStringLiteral("pf_mode");
    const QString INI_SCREEN_TILT_3      = QStringLiteral("pf_north_offset");
    const QString INI_SCREEN_TILT_4      = QStringLiteral("pf_min_num_per_sec");
    const QString INI_SCREEN_TILT_5      = QStringLiteral("pf_w_max");
    const QString INI_SCREEN_TILT_6      = QStringLiteral("pf_u_min");
    const QString INI_SCREEN_TILT_7      = QStringLiteral("pf_file");
    const QString INI_SCREEN_TILT_8      = QStringLiteral("pf_fix");
    const QString INI_SCREEN_TILT_PREFIX = QStringLiteral("pf_sect_");
    const QString INI_SCREEN_TILT_9      = QStringLiteral("width");
    const QString INI_SCREEN_TILT_10     = QStringLiteral("exclude");
    const QString INI_SCREEN_TILT_11     = QStringLiteral("pf_subset");

    const QString INIGROUP_TIMELAG_OPT = QStringLiteral("RawProcess_TimelagOptimization_Settings");
    const QString INI_TIMELAG_OPT_0    = QStringLiteral("to_start_date");
    const QString INI_TIMELAG_OPT_1    = QStringLiteral("to_end_date");
    const QString INI_TIMELAG_OPT_2    = QStringLiteral("to_mode");
    const QString INI_TIMELAG_OPT_3    = QStringLiteral("to_file");
    const QString INI_TIMELAG_OPT_4    = QStringLiteral("to_co2_min_flux");
    const QString INI_TIMELAG_OPT_5    = QStringLiteral("to_ch4_min_flux");
    const QString INI_TIMELAG_OPT_6    = QStringLiteral("to_gas4_min_flux");
    const QString INI_TIMELAG_OPT_7    = QStringLiteral("to_le_min_flux");
    const QString INI_TIMELAG_OPT_8    = QStringLiteral("to_pg_range");
    const QString INI_TIMELAG_OPT_9    = QStringLiteral("to_co2_min_lag");
    const QString INI_TIMELAG_OPT_10   = QStringLiteral("to_co2_max_lag");
    const QString INI_TIMELAG_OPT_11   = QStringLiteral("to_h2o_min_lag");
    const QString INI_TIMELAG_OPT_12   = QStringLiteral("to_h2o_max_lag");
    const QString INI_TIMELAG_OPT_13   = QStringLiteral("to_ch4_min_lag");
    const QString INI_TIMELAG_OPT_14   = QStringLiteral("to_ch4_max_lag");
    const QString INI_TIMELAG_OPT_15   = QStringLiteral("to_gas4_min_lag");
    const QString INI_TIMELAG_OPT_16   = QStringLiteral("to_gas4_max_lag");
    const QString INI_TIMELAG_OPT_17   = QStringLiteral("to_h2o_nclass");
    const QString INI_TIMELAG_OPT_18   = QStringLiteral("to_subset");

    const QString INIGROUP_RAND_ERROR = QStringLiteral("RawProcess_RandomUncertainty_Settings");
    const QString INI_RAND_ERROR_0    = QStringLiteral("ru_meth");
    const QString INI_RAND_ERROR_1    = QStringLiteral("ru_its_meth");
    const QString INI_RAND_ERROR_2    = QStringLiteral("ru_tlag_max");
    const QString INI_RAND_ERROR_3    = QStringLiteral("ru_its_sec_factor");

    const QString INIGROUP_BIOMET = QStringLiteral("RawProcess_BiometMeasurements");
    const QString INI_BIOMET_0    = QStringLiteral("biom_use_native_header");
    const QString INI_BIOMET_1    = QStringLiteral("biom_hlines");
    const QString INI_BIOMET_2    = QStringLiteral("biom_separator");
    const QString INI_BIOMET_3    = QStringLiteral("biom_tstamp_ref");
    const QString INI_BIOMET_4    = QStringLiteral("biom_ta");
    const QString INI_BIOMET_5    = QStringLiteral("biom_pa");
    const QString INI_BIOMET_6    = QStringLiteral("biom_rh");
    const QString INI_BIOMET_7    = QStringLiteral("biom_rg");
    const QString INI_BIOMET_8    = QStringLiteral("biom_lwin");
    const QString INI_BIOMET_9    = QStringLiteral("biom_ppfd");

} // namespace EcIni

#endif // ECINIDEFS_H
