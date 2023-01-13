#include "matmul.hpp"
NN_data layer_0[4][1][9] = {{{-0.08447296, -0.3626534, 0.3007769, 0.05620637, -0.21693799, -0.48197252, 0.50494784, 0.5163913, -0.4466335}},
                            {{0.29689246, -0.07532263, -0.15928352, -0.12037806, 0.09787049, 0.25151896, -0.036401063, 0.26763946, 0.40217522}},
                            {{0.15234487, 0.38468304, 0.50891095, -0.29206908, -0.17481138, -0.50153875, -0.51345694, 0.037263617, 0.4114425}},
                            {{0.19429278, -0.33654073, 0.5594786, 0.29341447, -0.38094807, -0.20315187, 0.034501404, 0.4442222, 0.41247064}}};
NN_data layer_1[4][4][9] = {{{0.16244479, 1.1309103, 1.2610255, -0.48654562, 0.40902343, 0.5557169, 0.07692924, 0.7922365, 1.0463165},
                             {0.113046564, 0.016110305, 0.74035853, -0.022220353, 0.18366322, 0.5436797, 0.2632493, -0.03688398, 0.38543943},
                             {-0.08956925, -0.12723069, 0.16367652, 0.56718284, 0.4657302, -0.051403396, 0.734713, 0.49999955, -0.6298945},
                             {0.12911935, 0.15569896, 0.78316003, 0.40377977, -0.14330432, 0.6462306, 1.0086774, 0.09664175, 0.68135923}},
                            {{0.20928246, 0.19039124, 0.050000977, -0.1167361, -0.11505575, -0.23839182, 0.06393959, -0.0006561124, -0.17147823},
                             {0.4456955, 0.3491435, -0.08599756, -0.073544204, -0.22419482, -0.085366495, -0.227111, -0.18357348, -0.3460699},
                             {0.33470786, 0.22112003, 0.064133205, 0.020659342, -0.3028519, -0.3650726, 0.1458587, 0.06493247, 0.006548123},
                             {-0.44840863, -0.3179985, -0.19711283, -0.18922278, -0.18123989, -0.14170206, 0.031853072, 0.1139456, 0.039344676}},
                            {{-0.121781155, -0.6239264, -0.32422423, -0.008420564, 0.5812239, 0.94243765, -0.46001592, -0.1178899, 0.24372625},
                             {0.25071573, 0.24103077, 0.8057304, 0.34175006, -0.14952345, 0.07482007, 0.19735195, -0.39638284, -0.053051054},
                             {0.5532031, -0.35907996, 0.68326646, 0.2825094, 0.5421039, 1.4095684, -0.26329654, -0.027725419, 0.6816088},
                             {0.4039831, 0.7327606, 0.3533962, 0.97426593, -0.17542213, 1.158131, 1.2763215, -0.24603617, 1.1086082}},
                            {{-0.094358444, 0.07586823, -0.14319757, 0.19929251, 0.032716133, -0.4644848, 0.22182739, 0.37462938, 0.042176597},
                             {0.37829039, 0.29723457, 0.4830995, -0.1427152, 0.3532821, -0.11380375, -0.099701926, -0.35726988, -0.114471875},
                             {0.22892159, 0.0296103, 0.16307461, 0.12344684, -0.22469541, -0.12256184, 0.2589987, 0.19985826, 0.16192804},
                             {-0.22108406, 0.042513292, -0.32701707, -0.25716195, -0.1434312, -0.19685599, 0.3326013, 0.28999335, 0.29501987}}};
NN_data layer_2[4][4][9] = {{{-0.28755662, -0.3158151, -0.02346491, 0.8997188, 0.047339626, 0.2636252, 0.81452626, 0.20010261, 0.41100672},
                             {-0.28890133, -0.2777719, -0.2093993, -0.07972059, 0.12233184, -0.049618233, -0.115454145, 0.09210849, -0.14403455},
                             {-0.29452184, 0.05429983, 0.14128305, -0.23078664, -0.042936828, 0.43097398, 0.018664485, 0.19274278, 0.3438543},
                             {0.03200877, -0.043213855, 0.58860606, 0.049694665, -0.06447708, 0.07096261, 0.22862498, -0.027666012, 0.3101767}},
                            {{-0.40166253, 0.5624926, -0.17240295, -0.15221372, 0.5511194, -0.63782036, -0.5568442, -0.295182, -0.5549449},
                             {-0.1598684, -0.23559463, 0.03709278, -0.07960728, 0.13130298, 0.19082892, -0.036657076, -0.03978102, -0.22367921},
                             {-0.5145016, -0.93390465, -2.5562127, -0.0077355797, -0.4429708, -2.6582031, -0.4676355, -0.5441877, -1.1621422},
                             {0.031643752, 0.36285838, -0.13437879, -0.15181783, 0.03935051, -0.747306, -0.6680819, 0.23981369, -0.8744922}},
                            {{-0.15684876, 0.07080942, -0.42169285, 0.55382717, 0.060216095, 0.020440752, 0.57741797, 0.33874896, 0.36962643},
                             {0.02055546, -0.09202024, -0.1819858, -0.1062903, -0.0094972905, 0.13072461, -0.080134064, -0.19029132, 0.008533856},
                             {0.102241375, 0.25090212, -0.31925008, 0.054177195, 0.32329357, -0.115621775, 0.07035372, 0.37105295, 0.08317067},
                             {0.20511639, 0.027450217, -0.38279778, -0.16439354, -0.20208465, -0.23586132, 0.06338856, 0.007199845, -0.22396223}},
                            {{-0.5904919, 0.09280475, 0.3426547, -0.26873133, 0.2745036, -0.06945335, -0.83020693, -0.26862875, -0.49686274},
                             {-0.18987885, 0.032306995, 0.19076766, -0.21921064, -0.27482033, 0.01607277, -0.26645863, -0.05816737, -0.2083777},
                             {-0.3558995, -0.112165526, -0.3005531, 0.01560892, 0.061323006, 0.12826589, -0.36557782, -0.32411042, -0.34359255},
                             {0.32792422, 0.24294019, 0.5922019, 0.23227437, 0.12079751, 0.4191613, 0.21729162, 0.3682752, 0.37343168}}};
const NN_data layer7_weights[] = {0.10877565, 0.1390758, -0.14997637, -0.04333767, -0.19859594, -0.16586673, 0.6636082, 0.35068667, -0.35733688, 0.120785445, 0.80803883, 0.22462171, -0.84461325, -0.25121486, 1.0362798, -0.14380981, 0.11712318, -0.21349296, 0.048198834, 0.12797548, -0.2123473, 0.009723232, 0.27788177, 0.43860912, 0.43239632, -0.30450764, 0.4387142, 0.30933845, 0.034340292, -0.026529783, 0.20890261, 0.24089168, -0.030836606, -0.3203027, -0.13893472, -0.17205966, -0.33699888, 0.11614544, 0.5997215, 0.13934886, -0.78451, -0.10898295, 0.8406573, -0.25536177, 0.24077727, -0.36887288, -0.69698614, 0.29120395, 0.18575974, 0.2885811, -0.28114143, 0.08850617, -0.61352783, -0.25459486, -0.06403088, -0.016596004, -0.41560245, 0.07255266, 0.57874775, 0.43057588, 0.31348497, -0.1246892, 0.41668865, 0.3079729, -0.030406633, -0.21937045, -0.012521581, 0.07359506, -0.64667344, -0.28579175, 0.35528088, 0.17233804, -0.84144175, -0.33630103, 0.34223238, 0.07017844, 0.5176425, 0.099947564, 1.1891565, 0.48841503, 0.06899422, 0.071245104, -0.31829637, -0.15406278, 0.18469793, -0.2964159, 0.5226452, 0.3426141, 0.20383348, -0.30469865, 0.18615094, 0.56927806, 0.5646412, 0.11473722, 0.023909757, -0.18103054, 0.4652446, 0.0055583073, 0.07964482, 0.14669852, -0.42222998, 0.16204862, 0.48079595, -0.16779108, -0.28382698, 0.1645663, 0.50496596, 0.11516049, -0.48083356, 0.054586466, -0.47135267, 0.32991678, 0.41110787, -0.06911734, 0.025031354, -0.3702807, -0.88998795, -0.32299247, 0.06926188, -0.2551655, -0.11005365, -0.08655693, -0.13406527, 0.5524909, 0.24526794, -0.2453324, 0.55092245, 0.40075397, -0.2014229, 0.063936576, -0.07438366, 0.17113861, -0.012929553, -0.0071633654, 0.57958025, 0.38665518, 0.08132878, -0.21268506, 0.25785616, 0.24098194, 0.37661996, 0.12675525, 0.1188393, 0.11656473, 0.010977783, -0.13447511, 0.1301329, 0.31181446, 0.35355887, 0.247503, 0.4732982, 0.5338263, 0.3100413, 0.15359774, 0.2986066, 0.48933774, 0.6196601, -0.20177528, 0.28831312, 0.07561236, 0.2922295, -0.25930753, 0.1609783, 0.23640202, -0.03802775, -0.19422804, 0.1925583, 0.32921663, -0.19508371, -0.22027636, 0.64334464, -0.14879714, 0.30774656, -0.23114249, 0.50506854, -0.22142327, 0.28562266, 0.30125925, -0.51322657, -0.79344076, 0.024505418, 0.16587703, -1.2410175, -0.63294464, -0.0013782642, 0.1334966, 0.06621972, -0.018073037, 0.0630855, 0.07283207, -0.28628987, 0.61696464, 0.2438014, -0.16747169, 0.34150186, -0.15491195, 0.35123718, 0.17131633, -0.35037613, -0.0018382305, -0.35503557, -0.04197337, -0.47541872, 0.03435865, 0.06318542, 0.1404784, 0.103356674, 0.04480476, 0.31867486, -0.08507964, 0.2995714, -0.2984637, 0.10028236, -0.18390171, -0.48353022, -0.5254476, 0.3156483, 0.16029309, -0.32498127, 0.23015074, -0.15571359, -0.33058968, -0.30129778, 0.43483406, 0.16081803, -0.1270724, 0.45660508, -0.27752736, 0.060119078, 0.06095211, 0.42207408, -0.32442787, 0.2094663, -0.010980436, -0.1282942, -0.20485228, -0.10823088, 0.009442521, -2.0890362, 0.2600046, 0.1685252, -0.23583929, -0.93034285, -0.78620523, -0.015434077, -0.13990082, -0.3953239, -0.28203934, 0.11509495, -0.3432465, -0.053087655, 0.2356667, 0.11612424, -0.08848375, -0.05987223, 0.44554827, -0.32320604, 0.1601545, -0.05576156, 0.16898963, -0.12730522, -0.22790243, 0.39484727, -0.33687374, -0.2936752, 0.2672325, 0.89584106, 0.09479483, -0.2817107, 0.06869612, 0.6807446, 0.16678649, 1.0602841, -0.2564955, -0.01524399, -0.20033483, 0.7450966, -0.24013196, -0.021552086, -0.007713887, -0.5056599, 0.12515797, -1.1080399, -0.18862051, -0.17630559, -0.2621895, -0.39851183, -0.1510714, -0.8323588, 0.24521479, 0.2422235, -0.18116489, 0.014852608, -0.0012470372, 0.8097928, -0.060451802, 0.29769596, 0.0658252, 0.6706743, 0.35353923, -0.2659137, 0.11050174, 0.087611884, 0.152706, 0.52465934, 0.051156383, -0.120474294, 0.033481445, 0.08881505, -0.26442024, -0.18028598, -0.12349067, -0.083347246, 0.26636976, -0.64876837, -0.2840703, 0.47550255, 0.29723403, -0.5726854, 0.2905456, 0.09410593, 0.07011764, 0.16255657, 0.07117088, -0.23200397, -0.16028187, 0.19014396, -0.08298506, -0.10030436, 0.039904468, -0.7238469, -0.14479919, 0.22256567, -0.2131326, -0.9956992, -0.5406045, -0.42802936, 0.0019757529, -0.009236313, -0.25271982, -0.7422601, -0.25347996, 0.35799542, -0.39438528, 0.21955283, 0.23627818, 0.32228288, 0.008696306, 0.09060366, -0.2488914, -0.11948941, 0.6027433, -0.12867853, -0.062362492, -0.62600535, 0.5215191, 0.21688464, 0.23889658, -0.5681577, -0.032469112, 0.08027352, 0.008336631, -0.21774001, -0.26869264, -0.023800407, 0.2211604, -0.31327036, -0.02533125, -0.25119105, -0.1003419, 0.35585558, 0.28114325, -0.313195, 0.32163632, 0.15148813, 0.1408141, 0.12846638, 0.15472843, 0.49927703, 0.42788818, 0.13131545, 0.32188827, 0.38255957, 0.40620837, 0.52332515, -0.009642905, 0.39784914, -0.11841782, -0.17329079, -0.23903152, 0.5352804, 0.15411253, -0.070462294, 0.31262025, 0.61239153, 0.059137646, 0.5139931, 0.28348726, 0.34896347, 0.7720561, -0.2245728, 0.059101105, 0.15219927, -0.043720763, -0.06501265, -0.15898106, -0.1196409, -0.13453862, -0.14038597, 0.1460723, 0.14827462, -0.08412689, -0.037521392, 0.32783374, 0.030490553, -0.32877418, -0.057749137, 0.27468646, 0.4996589, -0.26933408, 0.108577766, -0.29372123, -0.518027, -0.6931063, 0.16684565, -0.15632287, -1.123745, -0.22628751, -0.15755361, -0.26121107, 0.008518564, 0.40326577, 0.2992317, 0.23258854, -0.17659083, 0.1828459, -0.039963104, 0.10470164, -0.5294114, -0.30640835, -0.32023218, 0.04292992, -0.118404716, -0.25490084, -0.13120243, 0.1001873, 0.5654247, 0.5727794, 0.41123524, 0.13992713, 0.21444932, -0.298367, 0.107665315, 0.37328282, -0.0005622641, 0.43540993, -0.35997713, -0.057965357, 0.08784048, 0.0897787, -0.14784057, 0.27269298, 0.80993617, 0.15605566, -0.16130564, 0.30429485, -0.28124648, -0.16505545, -0.10990566, -0.19563663, 0.11276627, 0.25462627, -0.20766722, 0.25589186, 0.075304866, -0.31367198, -0.31563857, -0.20347622, -0.03359432, -0.20698015, 0.11212727, -0.2153606, 0.107049964, 0.18414456, 0.13223414, -0.0073550977, 0.08709387, -0.062440854, -0.060039222, -0.11419156, 0.4803363, 0.100733094, -0.28597805, -0.013606994, 0.5635129, -0.054778412, 0.46559554, -0.0581057, 0.6992577, 0.0465186, 0.13940409, 0.02992031, 0.09343224, -0.0065476377, -0.27340177, 0.3085191, -0.838768, -0.13516854, -0.09031317, 0.16814367, -0.7769848, -0.30008367};

const NN_data layer8_weights[] = {0.0041498556, -0.24667989, -0.016936101, 0.25777456, -0.36004582, 0.005959593, -0.13519418, 0.2137656, 0.065141186, -0.13095962, 0.1497353, -0.28882545, -0.2514023, -0.009333829, -0.22595194, 0.20014526, -0.12804426, -0.23945704, -0.06761735, -0.32562548, -0.27744004, -0.044382483, 0.19254318, -0.25627872, -0.21887894, -0.16034868, 0.0311593, -0.41082788, 0.24609818, 0.08216641, -0.025616359, 0.28342474, -0.22005194, 0.5149647, -0.8782125, 0.2409507, 1.0522652, 0.2022589, 0.874151, 0.5922394, 0.388435, 0.53631175, -0.07238452, 0.48595452, 0.471256, -0.66629034, 0.587056, -1.5636536, 0.8315322, 1.224529, 0.4994086, -0.28766268, 0.17991719, 0.80070615, 0.62280774, 0.0055276123, 0.48359358, 0.08883731, 0.77752566, 0.5455201, 0.67710584, 0.1028993, -0.00398905, -1.3795397, -1.19262, 0.51680416, -0.852892, 0.6076471, 1.4343798, 0.1587981, 0.92724466, 0.8452448, 0.11579593, 0.45296106, -0.038232762, 0.5731287, 0.5645242, 0.022693982, 0.48752704, -2.0277042, 0.30206418, 1.1257765, -0.15972029, -0.42960972, -0.47298113, 0.77257407, 0.39599746, 0.43590838, 0.47296095, 0.09709037, 0.09964827, 0.5960054, 0.2464427, -0.148623, -0.046081174, -1.4842964, 1.579811, 0.26874328, 0.6023053, 0.20546639, -0.6526218, 0.0811566, -0.24657324, -0.1661856, -0.03145994, 0.091217056, 0.29728368, 0.88154286, 0.2329973, -1.3899108, 0.89772034, -0.19377534, 1.3584852, -0.38687786, 0.5373228, -0.67600536, 2.0354295, 0.33897063, 0.9038733, -0.08708363, -0.0827454, -0.039947737, 1.8464154, -0.11062232, 0.7581373, 0.3627905, 0.2915395, 0.40706205, -0.39942166, -0.48456475, -1.2986218, 0.11388515, 0.5523648, 0.0998874, 1.109121, -0.58131456, -0.42059115, -0.1733381, 0.13614462, 0.9685866, 0.1297602, -0.16314515, 0.20909148, 0.10218999, 0.4981453, 0.993061, 0.059896857, 0.7206479, -0.37252733, -1.8275706, 0.42237514, -0.2159558, 0.34370005, -0.3623002, -0.72328544, 0.24861982, 0.07962668, 0.22668435, 0.04962737, 0.15652215, 0.5937511, -0.028118048, 1.4494256, 0.102271676, -2.4564216, -0.24077679, -1.4626573, 0.44201106, -0.5348585, -0.29087868, -0.16512822, -2.3175268, 0.6989602, 0.9354535, -0.19816934, 2.161287, -0.66764456, -1.54446, -2.708754, 0.6387948, 0.22603224, 0.59951216, -0.15058026, -0.29686582, 0.20792212, 0.15443926, -0.89721227, 0.8785001, 0.35891762, 0.34801164, -0.040498912, 0.62287647, -0.13511875, -0.027959758, -0.25623438, -0.2872886, 0.25104502, 0.07638066, -0.009927495, -0.26913697, 0.07893792, -0.20079039, 0.22214592, 0.17915598, -0.18935633, -0.16071546, -0.18226126, -0.112808645, -0.28578976, 0.024363775, 0.03364685, -0.16176128, -0.18820573, -0.020701528, -0.18353654, -0.093426876, -0.35073224, -0.02245307, -0.15963447, -0.33508322, 0.17147878, 0.07348892, 0.21379216, -0.06483071, -0.3046502, -0.28868273, -0.033886336, -0.13293922, 0.3802695, -0.31308112, 0.3456296, 0.044598054, 0.07668581, -0.14883864, 0.03283568, 0.17646973, 0.3657696, -0.21642591, -0.18178618, 0.2613116, 0.28188342, -0.007177794, -0.25590852, 0.024060305, -0.09634629, -0.08665264, 0.078311, -0.07020298, 0.027228225, 0.16922256, 0.009018894, -0.2194067, -0.30372468, -0.27831325, 0.10118302, 0.087065235, 1.7582161, -0.3803339, 2.1259878, 0.36432287, -2.8341055, -0.07418687, -0.8750934, -0.14396885, -0.07040938, -0.08157965, -0.24667513, -0.078163266, 0.66389227, 0.018155549, -0.4596471, 0.69806933, 0.8866188, -1.2606583, -1.7494218, 0.282758, 1.3431753, 0.6375995, 0.31888464, -0.13155636, -0.17435542, -0.24946561, 0.99234223, -0.23858513, 0.3927606, -0.18582606, 0.14407058, 1.057543, 0.140965, -0.23579897, 0.28679284, 0.29142332, -0.34599832, -0.2499645, -0.2529905, 0.1937099, -0.12933628, -0.24571493, 0.21222547, -0.27821687, 0.059317328, 0.1340001, -0.13380924, -0.15855661, -0.33876643, -0.3526775, 0.016669087, -0.21153015, -0.052237548, -0.2534816, -0.0035994947, -0.16066067, -0.30502114, 0.12067619, 0.14007357, 0.022442205, 0.00689121, 0.2386113, -0.2541716, -0.18923447, 0.41781762, 0.39471743, -0.1098946, 0.6443708, 0.44210795, -0.05614538, 0.17012185, 0.5599256, 0.3873142, 0.33642632, 0.5575198, 0.54202354, 0.6891125, -0.6782184, 0.6244754, -1.3632201, 1.0554863, 0.31321636, 0.23562439, -0.953747, 1.3093256, 0.52619326, 0.89869153, 0.45953012, 0.52934384, -0.0016660332, 0.9897336, 0.39097446, 0.8994573, -0.33516943, 0.3435155, -0.5310706, 0.6419343, 0.07850406, 0.16439158, 0.6129725, 0.072177425, 0.0036252888, 0.28421855, -0.14403345, -0.070882834, 0.035049178, 0.27483162, 0.7952258, 0.16634029, -1.1847879, 0.6007008, -1.1170951, 0.8944653, -0.19359456, 0.49801177, -0.7357921, 1.6304097, 1.0441575, 0.7296967, 0.3474362, -0.070603095, -0.17408271, 1.0372865, 0.31007954, 0.28881824, 0.10702443, 0.4193829, -0.26901445, 1.7574543, 0.035007693, 0.77303815, 0.44242334, -0.55228627, -0.35322163, -0.22874019, 0.24617603, 0.038565308, -0.4950699, 0.00784979, -0.81144834, 0.27669406, -1.3848469, 0.20187089, -1.3517082, 1.0231748, -0.75781447, 0.059846487, -1.2808173, 2.102954, 0.6340899, 0.99128085, 0.07556926, 0.078470595, -0.18319263, 0.851729, 0.72604626, 0.63498396, 0.09101948, 0.40739653, 0.23761083, -0.29454383, 0.2246897, -0.00834227, -0.016088724, 0.33150104, -0.0025343846, -0.18364304, -0.2757166, -0.04797203, -0.3241868, -0.30058357, 0.14891411, 0.03177763, 0.09469484, -0.010343118, 0.09376624, 0.0074840686, 0.0033744194, -0.00408998, 0.097198986, 0.23877616, 0.0815361, -0.03898837, -0.09162177, -0.2836029, 0.25972858, -0.28472933, -0.3071987, -0.20937465, 0.053759888, 0.053813618, 0.23368956, -0.20383668, -0.20853539, 0.09570129, -0.16550939, -0.05137598, 0.19327122, -0.050659873, -0.19737451, 0.105868764, -0.029116444, -0.24297337, -0.14721155, -0.12428031, 0.07846046, -0.11675845, -0.19762805, -0.18490036, -0.2378441, -0.35787055, -0.2530795, -0.056179844, 0.012259269, -0.31135833, 0.10430205, -0.15403104, -0.24372277, -0.24296226, 0.017119775, 0.14708813, -0.30454668, -0.10002454, -0.054922424, 1.2539669, -0.24339063, 2.5639067, 0.06405868, -1.9223527, 0.08520012, -1.4513212, 0.860449, -0.22887631, -0.22953664, 0.09057122, 0.022171224, 0.19821416, -0.20548162, 0.25355816, 0.22129364, 2.2090235, 0.05852983, -0.91979057, 0.51719743, 1.1886007, -0.7818136, -0.15930167, -0.24922922, -0.21702357, -0.12142644, 0.112084396, 0.43275648, 0.27447867, -0.3313569, -0.3771662, 0.7973745};

const NN_data layer9_weights[] = {-0.49245188, 0.6712891, 0.59273, 0.4543652, -1.794952, -4.1979136, -0.18143818, 0.55696905, -1.1962585, -0.35581446, 0.7891682, 0.9150395, 0.8300596, -0.25936472, -0.52621824, 0.88063437, 0.24932988, -0.17092845, -0.47092614, 0.71884876, 1.2903411, 1.0648614, -0.5376274, -0.41664466, 2.33871, -0.1411447, 0.32653847, 0.6784194, 0.82287043, -0.16553012, 0.43717346, -2.2568195};
