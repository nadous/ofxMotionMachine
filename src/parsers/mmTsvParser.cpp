#include "mmTsvParser.h"

/** Qualisys TSV format with header
Example file:

-------------------------------------
NO_OF_FRAMES	1401
NO_OF_CAMERAS	 --
NO_OF_MARKERS	68
FREQUENCY	179
NO_OF_ANALOG	0
ANALOG_FREQUENCY	0
DESCRIPTION	 --
TIME_STAMP	 	2016-01-22, 10:24:41	6265.58734026
DATA_INCLUDED	 3D
MARKER_NAMES	L_IAS	L_IPS	R_IPS	R_IAS	L_TH1	L_TH2	L_TH3	L_TH4	L_SK1	L_SK2	L_SK3	L_SK4	L_FCC	L_FM1	L_FM2	L_FM5	R_TH1	R_TH2	R_TH3	R_TH4	R_SK1	R_SK2	R_SK3	R_SK4	R_FCC	R_FM1	R_FM2	R_FM5	L_FTC	R_FTC	L_FLE	R_FME	R_FLE	L_FME	R_FAL	L_TAM	L_FAL	R_TAM	LBHD	RBHD	RFHD	LFHD	CLAV	CV7	STRN	TV10	LAC	RAC	L_RSP	L_USP	L_HL5	L_HM1	LF1	LF2	RF1	RF2	R_HL5	R_HM1	R_USP	R_RSP	L_HLE	L_HME	R_HME	R_HLE	LUA1	LUA2	RUA1	RUA2
(optional line: column headers)L_IAS X	L_IAS Y	L_IAS Z	L_IPS X	L_IPS Y	L_IPS Z	R_IPS X	R_IPS Y	R_IPS Z	R_IAS X	R_IAS Y	R_IAS Z	L_TH1 X	L_TH1 Y	L_TH1 Z	L_TH2 X	L_TH2 Y	L_TH2 Z	L_TH3 X	L_TH3 Y	L_TH3 Z	L_TH4 X	L_TH4 Y	L_TH4 Z	L_SK1 X	L_SK1 Y	L_SK1 Z	L_SK2 X	L_SK2 Y	L_SK2 Z	L_SK3 X	L_SK3 Y	L_SK3 Z	L_SK4 X	L_SK4 Y	L_SK4 Z	L_FCC X	L_FCC Y	L_FCC Z	L_FM1 X	L_FM1 Y	L_FM1 Z	L_FM2 X	L_FM2 Y	L_FM2 Z	L_FM5 X	L_FM5 Y	L_FM5 Z	R_TH1 X	R_TH1 Y	R_TH1 Z	R_TH2 X	R_TH2 Y	R_TH2 Z	R_TH3 X	R_TH3 Y	R_TH3 Z	R_TH4 X	R_TH4 Y	R_TH4 Z	R_SK1 X	R_SK1 Y	R_SK1 Z	R_SK2 X	R_SK2 Y	R_SK2 Z	R_SK3 X	R_SK3 Y	R_SK3 Z	R_SK4 X	R_SK4 Y	R_SK4 Z	R_FCC X	R_FCC Y	R_FCC Z	R_FM1 X	R_FM1 Y	R_FM1 Z	R_FM2 X	R_FM2 Y	R_FM2 Z	R_FM5 X	R_FM5 Y	R_FM5 Z	L_FTC X	L_FTC Y	L_FTC Z	R_FTC X	R_FTC Y	R_FTC Z	L_FLE X	L_FLE Y	L_FLE Z	R_FME X	R_FME Y	R_FME Z	R_FLE X	R_FLE Y	R_FLE Z	L_FME X	L_FME Y	L_FME Z	R_FAL X	R_FAL Y	R_FAL Z	L_TAM X	L_TAM Y	L_TAM Z	L_FAL X	L_FAL Y	L_FAL Z	R_TAM X	R_TAM Y	R_TAM Z	LBHD X	LBHD Y	LBHD Z	RBHD X	RBHD Y	RBHD Z	RFHD X	RFHD Y	RFHD Z	LFHD X	LFHD Y	LFHD Z	CLAV X	CLAV Y	CLAV Z	CV7 X	CV7 Y	CV7 Z	STRN X	STRN Y	STRN Z	TV10 X	TV10 Y	TV10 Z	LAC X	LAC Y	LAC Z	RAC X	RAC Y	RAC Z	L_RSP X	L_RSP Y	L_RSP Z	L_USP X	L_USP Y	L_USP Z	L_HL5 X	L_HL5 Y	L_HL5 Z	L_HM1 X	L_HM1 Y	L_HM1 Z	LF1 X	LF1 Y	LF1 Z	LF2 X	LF2 Y	LF2 Z	RF1 X	RF1 Y	RF1 Z	RF2 X	RF2 Y	RF2 Z	R_HL5 X	R_HL5 Y	R_HL5 Z	R_HM1 X	R_HM1 Y	R_HM1 Z	R_USP X	R_USP Y	R_USP Z	R_RSP X	R_RSP Y	R_RSP Z	L_HLE X	L_HLE Y	L_HLE Z	L_HME X	L_HME Y	L_HME Z	R_HME X	R_HME Y	R_HME Z	R_HLE X	R_HLE Y	R_HLE Z	LUA1 X	LUA1 Y	LUA1 Z	LUA2 X	LUA2 Y	LUA2 Z	RUA1 X	RUA1 Y	RUA1 Z	RUA2 X	RUA2 Y	RUA2 Z	
-166.799	233.895	1073.066	-410.646	203.184	1088.995	-409.059	-35.823	1087.794	-178.953	-69.568	1069.297	-209.298	305.897	906.229	-314.417	328.953	876.393	-328.316	337.486	767.931	-231.941	329.384	752.189	-310.596	412.747	439.291	-388.495	391.271	479.986	-387.254	420.431	341.197	-316.183	428.549	355.752	-417.366	400.646	48.719	-138.259	413.599	63.728	-186.482	427.806	87.425	-148.587	501.083	48.372	-320.117	-145.949	844.048	-232.650	-146.175	887.305	-239.540	-164.350	765.067	-317.377	-156.564	747.073	-373.670	-237.153	396.539	-311.144	-247.538	424.140	-309.887	-263.518	320.265	-358.384	-257.380	292.865	-392.609	-237.611	49.848	-125.204	-263.304	64.021	-181.496	-282.275	94.196	-148.196	-342.554	60.386	-285.088	302.207	1012.305	-263.808	-127.686	1009.757	-304.342	373.833	573.354	-278.478	-60.633	505.068	-326.669	-201.558	556.435	-290.017	228.559	542.791	-296.554	-192.026	101.433	-365.386	460.189	105.428	-321.132	352.759	97.580	-344.911	-299.594	102.475	-309.048	141.961	1813.211	-304.585	-3.940	1814.698	-161.088	2.137	1873.802	-157.802	129.090	1878.585	-196.394	87.732	1554.132	-399.436	82.462	1617.470	-143.091	88.267	1379.776	-425.153	79.836	1190.252	-301.670	317.499	1596.151	-292.967	-129.958	1586.442	-199.557	374.677	955.393	-279.568	410.069	937.671	-246.628	438.559	876.562	-191.608	426.834	892.956	-304.573	403.097	1111.229	-318.434	378.949	1005.900	-260.039	-178.677	1120.225	-282.254	-236.966	1038.880	-271.278	-265.857	864.827	-230.089	-254.169	874.087	-317.810	-227.773	932.747	-227.338	-185.940	949.283	-344.365	375.796	1211.403	-365.395	287.675	1199.185	-376.287	-111.962	1194.421	-329.015	-227.794	1215.933	-327.728	364.244	1438.688	-377.080	335.951	1292.633	-292.782	-189.533	1411.346	-373.159	-192.251	1329.357
-166.584	233.686	1073.026	-410.405	203.037	1088.965	-408.913	-36.008	1087.819	-178.797	-69.808	1069.287	-208.930	305.672	906.246	-314.143	328.824	876.434	-328.034	337.372	767.924	-231.666	329.152	752.152	-310.422	412.624	439.331	-388.302	391.190	480.024	-387.097	420.357	341.203	-316.019	428.457	355.720	-417.382	400.615	48.704	-138.242	413.579	63.699	-186.480	427.802	87.415	-148.558	501.064	48.370	-320.145	-146.126	844.081	-232.591	-146.325	887.189	-239.619	-164.392	764.997	-317.524	-156.668	747.088	-373.984	-237.113	396.456	-311.559	-247.528	424.100	-310.210	-263.594	320.248	-358.653	-257.390	292.871	-392.616	-237.622	49.836	-125.250	-263.345	64.052	-181.514	-282.321	94.184	-148.196	-342.578	60.361	-284.817	302.008	1012.223	-263.604	-127.883	1009.696	-304.018	373.691	573.429	-278.826	-60.667	505.116	-327.149	-201.555	556.482	-289.851	228.395	542.727	-296.522	-192.122	101.421	-365.371	460.107	105.456	-321.110	352.692	97.580	-345.003	-299.668	102.419	-309.050	141.844	1813.180	-304.633	-4.077	1814.654	-161.150	1.989	1873.852	-157.822	128.952	1878.601	-196.314	87.535	1554.125	-399.328	82.323	1617.429	-142.892	88.087	1379.824	-424.901	79.694	1190.221	-301.538	317.346	1596.120	-292.950	-130.117	1586.444	-199.605	374.705	955.293	-279.621	410.035	937.659	-246.709	438.570	876.596	-191.673	426.857	892.954	-304.553	403.027	1111.237	-318.329	378.901	1005.762	-260.003	-178.837	1120.200	-282.204	-237.086	1038.874	-271.300	-265.968	864.719	-230.092	-254.272	874.023	-317.813	-227.931	932.727	-227.286	-186.081	949.306	-344.293	375.688	1211.366	-365.312	287.552	1199.186	-376.230	-112.112	1194.378	-328.961	-227.934	1215.918	-327.611	364.101	1438.666	-376.986	335.748	1292.635	-292.739	-189.684	1411.327	-373.144	-192.388	1329.359
-166.369	233.465	1072.978	-410.160	202.875	1088.937	-408.734	-36.214	1087.805	-178.559	-70.024	1069.277	-208.656	305.452	906.223	-313.896	328.662	876.460	-327.747	337.263	767.894	-231.416	328.971	752.124	-310.201	412.519	439.316	-388.084	391.144	480.059	-386.929	420.310	341.215	-315.858	428.351	355.727	-417.375	400.617	48.747	-138.188	413.562	63.666	-186.472	427.781	87.418	-148.571	501.056	48.331	-320.131	-146.297	844.076	-232.516	-146.436	887.114	-239.710	-164.440	764.888	-317.658	-156.765	747.096	-374.344	-237.077	396.453	-311.983	-247.553	424.099	-310.528	-263.643	320.272	-358.958	-257.380	292.868	-393.400	-237.161	50.617	-125.247	-263.389	64.080	-181.531	-282.403	94.200	-148.235	-342.618	60.327	-284.556	301.798	1012.161	-263.494	-128.062	1009.649	-303.767	373.533	573.393	-279.200	-60.699	505.091	-327.491	-201.568	556.443	-289.687	228.229	542.739	-296.581	-192.207	101.476	-365.313	460.052	105.506	-321.106	352.631	97.553	-345.057	-299.703	102.421	-309.030	141.706	1813.126	-304.643	-4.199	1814.626	-161.214	1.821	1873.905	-157.852	128.791	1878.643	-196.270	87.379	1554.097	-399.215	82.200	1617.357	-142.734	87.900	1379.832	-424.679	79.552	1190.193	-301.398	317.202	1596.055	-292.891	-130.280	1586.417	-199.659	374.704	955.244	-279.647	409.978	937.626	-246.753	438.548	876.568	-191.728	426.867	892.908	-304.513	402.934	1111.218	-318.287	378.858	1005.748	-259.964	-178.985	1120.203	-282.188	-237.223	1038.888	-271.336	-266.087	864.700	-230.087	-254.381	873.993	-317.805	-228.076	932.716	-227.274	-186.244	949.273	-344.270	375.548	1211.362	-365.252	287.428	1199.171	-376.089	-112.221	1194.389	-328.887	-228.057	1215.892	-327.487	363.955	1438.617	-376.899	335.602	1292.628	-292.663	-189.836	1411.301	-373.096	-192.518	1329.349
-165.592	233.488	1073.045	-409.989	202.777	1088.896	-408.539	-36.382	1087.852	-178.454	-70.245	1069.260	-208.400	305.160	906.198	-313.652	328.511	876.480	-327.411	336.921	767.985	-231.195	328.766	752.121	-310.420	412.165	439.660	-388.027	391.133	480.029	-386.813	420.220	341.265	-315.700	428.262	355.700	-417.223	400.652	48.569	-138.201	413.588	63.616	-186.448	427.745	87.399	-148.545	501.037	48.345	-320.237	-146.488	844.047	-233.008	-146.377	886.941	-239.887	-164.095	764.881	-317.794	-156.880	747.067	-374.446	-237.376	396.747	-312.631	-247.410	424.067	-311.194	-263.799	320.470	-359.277	-257.303	292.818	-392.491	-237.751	49.766	-125.311	-263.424	64.105	-181.656	-282.043	93.907	-148.929	-343.148	60.470	-284.532	301.665	1011.986	-263.320	-128.226	1009.619	-303.581	373.280	573.297	-279.613	-60.785	505.064	-328.052	-201.458	556.445	-289.752	228.169	542.643	-296.577	-192.313	101.522	-365.308	459.939	105.618	-321.112	352.590	97.545	-344.987	-299.612	102.356	-309.021	141.581	1813.047	-304.662	-4.337	1814.570	-161.380	1.462	1874.112	-157.854	128.631	1878.683	-196.163	87.160	1554.054	-399.057	82.084	1617.558	-142.604	87.674	1379.764	-424.868	79.199	1190.519	-301.247	317.039	1596.016	-292.913	-130.428	1586.390	-199.643	374.470	955.200	-279.449	409.968	937.577	-246.772	438.445	876.517	-191.786	427.561	893.214	-304.596	402.736	1111.161	-318.185	377.849	1005.887	-261.925	-178.562	1119.065	-282.176	-237.329	1038.841	-271.127	-266.100	864.564	-229.956	-254.345	873.733	-317.996	-228.152	932.654	-227.790	-186.197	948.720	-344.305	375.083	1211.319	-365.072	287.376	1198.986	-375.946	-112.365	1194.157	-328.775	-228.126	1215.831	-327.493	363.861	1438.605	-376.789	335.605	1293.037	-292.930	-189.919	1411.041	-373.038	-192.642	1329.330
-165.282	233.238	1073.057	-409.764	202.622	1088.883	-408.374	-36.570	1087.845	-178.382	-70.499	1069.239	-208.150	304.919	906.157	-313.328	328.313	876.416	-327.148	336.733	767.985	-231.067	328.529	752.150	-310.310	412.039	439.698	-387.844	390.990	480.102	-386.697	420.088	341.302	-315.600	428.129	355.757	-417.225	400.663	48.600	-138.186	413.481	63.646	-186.406	427.656	87.478	-148.534	500.992	48.362	-320.278	-146.660	844.007	-232.983	-146.554	886.940	-240.054	-164.133	764.781	-318.010	-156.996	747.080	-374.846	-237.316	396.717	-313.053	-247.501	424.135	-311.590	-263.875	320.473	-359.589	-257.297	292.772	-392.434	-237.787	49.719	-125.351	-263.514	64.181	-181.717	-282.198	93.976	-148.976	-343.280	60.492	-284.486	301.350	1011.891	-263.243	-128.411	1009.589	-303.428	373.098	573.314	-280.000	-60.894	505.051	-328.528	-201.542	556.493	-289.659	227.947	542.683	-296.633	-192.538	101.687	-365.306	459.842	105.702	-321.135	352.527	97.590	-345.057	-299.724	102.303	-308.912	141.411	1812.940	-304.701	-4.476	1814.529	-161.415	1.267	1874.195	-157.913	128.420	1878.785	-196.092	86.956	1554.114	-398.855	81.857	1617.421	-142.512	87.408	1379.767	-424.667	79.002	1190.518	-301.091	316.839	1595.985	-292.832	-130.642	1586.528	-199.618	374.366	955.139	-279.481	409.773	937.555	-246.865	438.372	876.560	-191.814	427.479	893.222	-304.576	402.623	1111.151	-318.118	377.727	1005.830	-261.891	-178.695	1119.116	-282.149	-237.502	1038.869	-271.230	-266.335	864.568	-229.927	-254.510	873.706	-317.949	-228.260	932.580	-227.774	-186.437	948.700	-344.220	374.847	1211.281	-365.030	287.217	1198.954	-375.865	-112.601	1194.149	-328.706	-228.260	1215.862	-327.347	363.636	1438.568	-376.640	335.426	1292.950	-292.899	-190.121	1411.048	-373.004	-192.764	1329.294
-164.964	232.991	1073.059	-409.542	202.426	1088.831	-408.206	-36.743	1087.813	-178.168	-70.781	1069.258	-207.916	304.673	906.114	-313.074	328.120	876.387	-326.921	336.534	767.989	-230.876	328.337	752.111	-310.215	411.917	439.703	-387.728	390.908	480.103	-386.601	420.016	341.309	-315.502	428.047	355.742	-417.232	400.680	48.567	-138.157	413.474	63.671	-186.406	427.644	87.491	-148.533	500.967	48.385	-320.292	-146.825	844.025	-232.930	-146.713	886.867	-240.171	-164.180	764.686	-318.143	-157.111	747.066	-375.263	-237.278	396.694	-313.469	-247.546	424.144	-311.934	-263.959	320.534	-359.882	-257.289	292.763	-392.447	-237.794	49.714	-125.393	-263.570	64.231	-181.766	-282.300	93.996	-148.965	-343.302	60.484	-283.861	300.805	1011.751	-263.143	-128.604	1009.510	-303.280	372.936	573.292	-280.328	-60.990	505.071	-328.883	-201.573	556.473	-289.566	227.789	542.613	-296.651	-192.645	101.704	-365.298	459.797	105.726	-321.144	352.490	97.612	-345.149	-299.782	102.282	-308.848	141.263	1812.869	-304.712	-4.619	1814.484	-161.463	1.073	1874.238	-157.908	128.245	1878.836	-195.983	86.791	1554.117	-398.727	81.686	1617.351	-142.392	87.202	1379.733	-424.436	78.859	1190.442	-300.932	316.670	1595.959	-292.732	-130.806	1586.520	-199.603	374.263	955.128	-279.504	409.603	937.499	-246.836	438.255	876.523	-191.819	427.399	893.181	-304.513	402.506	1111.089	-318.053	377.574	1005.790	-261.903	-178.818	1119.036	-282.080	-237.623	1038.836	-271.265	-266.454	864.517	-229.952	-254.627	873.660	-317.940	-228.384	932.554	-227.787	-186.585	948.650	-344.198	374.659	1211.242	-364.942	287.044	1198.886	-375.772	-112.746	1194.133	-328.681	-228.414	1215.843	-327.260	363.464	1438.532	-376.558	335.236	1292.921	-292.784	-190.305	1411.040	-372.913	-192.902	1329.284
...
--------------------------------------
optional columns (from line 11) if timestamps included:
(optional line: column headers)Frame	Time	L_IAS X	L_IAS Y	L_IAS Z	L_IPS X	L_IPS Y	L_IPS Z	R_IPS X	R_IPS Y	R_IPS Z	R_IAS X	R_IAS Y	R_IAS Z	L_TH1 X	L_TH1 Y	L_TH1 Z	L_TH2 X	L_TH2 Y	L_TH2 Z	L_TH3 X	L_TH3 Y	L_TH3 Z	L_TH4 X	L_TH4 Y	L_TH4 Z	L_SK1 X	L_SK1 Y	L_SK1 Z	L_SK2 X	L_SK2 Y	L_SK2 Z	L_SK3 X	L_SK3 Y	L_SK3 Z	L_SK4 X	L_SK4 Y	L_SK4 Z	L_FCC X	L_FCC Y	L_FCC Z	L_FM1 X	L_FM1 Y	L_FM1 Z	L_FM2 X	L_FM2 Y	L_FM2 Z	L_FM5 X	L_FM5 Y	L_FM5 Z	R_TH1 X	R_TH1 Y	R_TH1 Z	R_TH2 X	R_TH2 Y	R_TH2 Z	R_TH3 X	R_TH3 Y	R_TH3 Z	R_TH4 X	R_TH4 Y	R_TH4 Z	R_SK1 X	R_SK1 Y	R_SK1 Z	R_SK2 X	R_SK2 Y	R_SK2 Z	R_SK3 X	R_SK3 Y	R_SK3 Z	R_SK4 X	R_SK4 Y	R_SK4 Z	R_FCC X	R_FCC Y	R_FCC Z	R_FM1 X	R_FM1 Y	R_FM1 Z	R_FM2 X	R_FM2 Y	R_FM2 Z	R_FM5 X	R_FM5 Y	R_FM5 Z	L_FTC X	L_FTC Y	L_FTC Z	R_FTC X	R_FTC Y	R_FTC Z	L_FLE X	L_FLE Y	L_FLE Z	R_FME X	R_FME Y	R_FME Z	R_FLE X	R_FLE Y	R_FLE Z	L_FME X	L_FME Y	L_FME Z	R_FAL X	R_FAL Y	R_FAL Z	L_TAM X	L_TAM Y	L_TAM Z	L_FAL X	L_FAL Y	L_FAL Z	R_TAM X	R_TAM Y	R_TAM Z	LBHD X	LBHD Y	LBHD Z	RBHD X	RBHD Y	RBHD Z	RFHD X	RFHD Y	RFHD Z	LFHD X	LFHD Y	LFHD Z	CLAV X	CLAV Y	CLAV Z	CV7 X	CV7 Y	CV7 Z	STRN X	STRN Y	STRN Z	TV10 X	TV10 Y	TV10 Z	LAC X	LAC Y	LAC Z	RAC X	RAC Y	RAC Z	L_RSP X	L_RSP Y	L_RSP Z	L_USP X	L_USP Y	L_USP Z	L_HL5 X	L_HL5 Y	L_HL5 Z	L_HM1 X	L_HM1 Y	L_HM1 Z	LF1 X	LF1 Y	LF1 Z	LF2 X	LF2 Y	LF2 Z	RF1 X	RF1 Y	RF1 Z	RF2 X	RF2 Y	RF2 Z	R_HL5 X	R_HL5 Y	R_HL5 Z	R_HM1 X	R_HM1 Y	R_HM1 Z	R_USP X	R_USP Y	R_USP Z	R_RSP X	R_RSP Y	R_RSP Z	L_HLE X	L_HLE Y	L_HLE Z	L_HME X	L_HME Y	L_HME Z	R_HME X	R_HME Y	R_HME Z	R_HLE X	R_HLE Y	R_HLE Z	LUA1 X	LUA1 Y	LUA1 Z	LUA2 X	LUA2 Y	LUA2 Z	RUA1 X	RUA1 Y	RUA1 Z	RUA2 X	RUA2 Y	RUA2 Z	
1	0.00000	-166.799	233.895	1073.066	-410.646	203.184	1088.995	-409.059	-35.823	1087.794	-178.953	-69.568	1069.297	-209.298	305.897	906.229	-314.417	328.953	876.393	-328.316	337.486	767.931	-231.941	329.384	752.189	-310.596	412.747	439.291	-388.495	391.271	479.986	-387.254	420.431	341.197	-316.183	428.549	355.752	-417.366	400.646	48.719	-138.259	413.599	63.728	-186.482	427.806	87.425	-148.587	501.083	48.372	-320.117	-145.949	844.048	-232.650	-146.175	887.305	-239.540	-164.350	765.067	-317.377	-156.564	747.073	-373.670	-237.153	396.539	-311.144	-247.538	424.140	-309.887	-263.518	320.265	-358.384	-257.380	292.865	-392.609	-237.611	49.848	-125.204	-263.304	64.021	-181.496	-282.275	94.196	-148.196	-342.554	60.386	-285.088	302.207	1012.305	-263.808	-127.686	1009.757	-304.342	373.833	573.354	-278.478	-60.633	505.068	-326.669	-201.558	556.435	-290.017	228.559	542.791	-296.554	-192.026	101.433	-365.386	460.189	105.428	-321.132	352.759	97.580	-344.911	-299.594	102.475	-309.048	141.961	1813.211	-304.585	-3.940	1814.698	-161.088	2.137	1873.802	-157.802	129.090	1878.585	-196.394	87.732	1554.132	-399.436	82.462	1617.470	-143.091	88.267	1379.776	-425.153	79.836	1190.252	-301.670	317.499	1596.151	-292.967	-129.958	1586.442	-199.557	374.677	955.393	-279.568	410.069	937.671	-246.628	438.559	876.562	-191.608	426.834	892.956	-304.573	403.097	1111.229	-318.434	378.949	1005.900	-260.039	-178.677	1120.225	-282.254	-236.966	1038.880	-271.278	-265.857	864.827	-230.089	-254.169	874.087	-317.810	-227.773	932.747	-227.338	-185.940	949.283	-344.365	375.796	1211.403	-365.395	287.675	1199.185	-376.287	-111.962	1194.421	-329.015	-227.794	1215.933	-327.728	364.244	1438.688	-377.080	335.951	1292.633	-292.782	-189.533	1411.346	-373.159	-192.251	1329.357
2	0.00559	-166.584	233.686	1073.026	-410.405	203.037	1088.965	-408.913	-36.008	1087.819	-178.797	-69.808	1069.287	-208.930	305.672	906.246	-314.143	328.824	876.434	-328.034	337.372	767.924	-231.666	329.152	752.152	-310.422	412.624	439.331	-388.302	391.190	480.024	-387.097	420.357	341.203	-316.019	428.457	355.720	-417.382	400.615	48.704	-138.242	413.579	63.699	-186.480	427.802	87.415	-148.558	501.064	48.370	-320.145	-146.126	844.081	-232.591	-146.325	887.189	-239.619	-164.392	764.997	-317.524	-156.668	747.088	-373.984	-237.113	396.456	-311.559	-247.528	424.100	-310.210	-263.594	320.248	-358.653	-257.390	292.871	-392.616	-237.622	49.836	-125.250	-263.345	64.052	-181.514	-282.321	94.184	-148.196	-342.578	60.361	-284.817	302.008	1012.223	-263.604	-127.883	1009.696	-304.018	373.691	573.429	-278.826	-60.667	505.116	-327.149	-201.555	556.482	-289.851	228.395	542.727	-296.522	-192.122	101.421	-365.371	460.107	105.456	-321.110	352.692	97.580	-345.003	-299.668	102.419	-309.050	141.844	1813.180	-304.633	-4.077	1814.654	-161.150	1.989	1873.852	-157.822	128.952	1878.601	-196.314	87.535	1554.125	-399.328	82.323	1617.429	-142.892	88.087	1379.824	-424.901	79.694	1190.221	-301.538	317.346	1596.120	-292.950	-130.117	1586.444	-199.605	374.705	955.293	-279.621	410.035	937.659	-246.709	438.570	876.596	-191.673	426.857	892.954	-304.553	403.027	1111.237	-318.329	378.901	1005.762	-260.003	-178.837	1120.200	-282.204	-237.086	1038.874	-271.300	-265.968	864.719	-230.092	-254.272	874.023	-317.813	-227.931	932.727	-227.286	-186.081	949.306	-344.293	375.688	1211.366	-365.312	287.552	1199.186	-376.230	-112.112	1194.378	-328.961	-227.934	1215.918	-327.611	364.101	1438.666	-376.986	335.748	1292.635	-292.739	-189.684	1411.327	-373.144	-192.388	1329.359
3	0.01117	-166.369	233.465	1072.978	-410.160	202.875	1088.937	-408.734	-36.214	1087.805	-178.559	-70.024	1069.277	-208.656	305.452	906.223	-313.896	328.662	876.460	-327.747	337.263	767.894	-231.416	328.971	752.124	-310.201	412.519	439.316	-388.084	391.144	480.059	-386.929	420.310	341.215	-315.858	428.351	355.727	-417.375	400.617	48.747	-138.188	413.562	63.666	-186.472	427.781	87.418	-148.571	501.056	48.331	-320.131	-146.297	844.076	-232.516	-146.436	887.114	-239.710	-164.440	764.888	-317.658	-156.765	747.096	-374.344	-237.077	396.453	-311.983	-247.553	424.099	-310.528	-263.643	320.272	-358.958	-257.380	292.868	-393.400	-237.161	50.617	-125.247	-263.389	64.080	-181.531	-282.403	94.200	-148.235	-342.618	60.327	-284.556	301.798	1012.161	-263.494	-128.062	1009.649	-303.767	373.533	573.393	-279.200	-60.699	505.091	-327.491	-201.568	556.443	-289.687	228.229	542.739	-296.581	-192.207	101.476	-365.313	460.052	105.506	-321.106	352.631	97.553	-345.057	-299.703	102.421	-309.030	141.706	1813.126	-304.643	-4.199	1814.626	-161.214	1.821	1873.905	-157.852	128.791	1878.643	-196.270	87.379	1554.097	-399.215	82.200	1617.357	-142.734	87.900	1379.832	-424.679	79.552	1190.193	-301.398	317.202	1596.055	-292.891	-130.280	1586.417	-199.659	374.704	955.244	-279.647	409.978	937.626	-246.753	438.548	876.568	-191.728	426.867	892.908	-304.513	402.934	1111.218	-318.287	378.858	1005.748	-259.964	-178.985	1120.203	-282.188	-237.223	1038.888	-271.336	-266.087	864.700	-230.087	-254.381	873.993	-317.805	-228.076	932.716	-227.274	-186.244	949.273	-344.270	375.548	1211.362	-365.252	287.428	1199.171	-376.089	-112.221	1194.389	-328.887	-228.057	1215.892	-327.487	363.955	1438.617	-376.899	335.602	1292.628	-292.663	-189.836	1411.301	-373.096	-192.518	1329.349
4	0.01676	-165.592	233.488	1073.045	-409.989	202.777	1088.896	-408.539	-36.382	1087.852	-178.454	-70.245	1069.260	-208.400	305.160	906.198	-313.652	328.511	876.480	-327.411	336.921	767.985	-231.195	328.766	752.121	-310.420	412.165	439.660	-388.027	391.133	480.029	-386.813	420.220	341.265	-315.700	428.262	355.700	-417.223	400.652	48.569	-138.201	413.588	63.616	-186.448	427.745	87.399	-148.545	501.037	48.345	-320.237	-146.488	844.047	-233.008	-146.377	886.941	-239.887	-164.095	764.881	-317.794	-156.880	747.067	-374.446	-237.376	396.747	-312.631	-247.410	424.067	-311.194	-263.799	320.470	-359.277	-257.303	292.818	-392.491	-237.751	49.766	-125.311	-263.424	64.105	-181.656	-282.043	93.907	-148.929	-343.148	60.470	-284.532	301.665	1011.986	-263.320	-128.226	1009.619	-303.581	373.280	573.297	-279.613	-60.785	505.064	-328.052	-201.458	556.445	-289.752	228.169	542.643	-296.577	-192.313	101.522	-365.308	459.939	105.618	-321.112	352.590	97.545	-344.987	-299.612	102.356	-309.021	141.581	1813.047	-304.662	-4.337	1814.570	-161.380	1.462	1874.112	-157.854	128.631	1878.683	-196.163	87.160	1554.054	-399.057	82.084	1617.558	-142.604	87.674	1379.764	-424.868	79.199	1190.519	-301.247	317.039	1596.016	-292.913	-130.428	1586.390	-199.643	374.470	955.200	-279.449	409.968	937.577	-246.772	438.445	876.517	-191.786	427.561	893.214	-304.596	402.736	1111.161	-318.185	377.849	1005.887	-261.925	-178.562	1119.065	-282.176	-237.329	1038.841	-271.127	-266.100	864.564	-229.956	-254.345	873.733	-317.996	-228.152	932.654	-227.790	-186.197	948.720	-344.305	375.083	1211.319	-365.072	287.376	1198.986	-375.946	-112.365	1194.157	-328.775	-228.126	1215.831	-327.493	363.861	1438.605	-376.789	335.605	1293.037	-292.930	-189.919	1411.041	-373.038	-192.642	1329.330
5	0.02235	-165.282	233.238	1073.057	-409.764	202.622	1088.883	-408.374	-36.570	1087.845	-178.382	-70.499	1069.239	-208.150	304.919	906.157	-313.328	328.313	876.416	-327.148	336.733	767.985	-231.067	328.529	752.150	-310.310	412.039	439.698	-387.844	390.990	480.102	-386.697	420.088	341.302	-315.600	428.129	355.757	-417.225	400.663	48.600	-138.186	413.481	63.646	-186.406	427.656	87.478	-148.534	500.992	48.362	-320.278	-146.660	844.007	-232.983	-146.554	886.940	-240.054	-164.133	764.781	-318.010	-156.996	747.080	-374.846	-237.316	396.717	-313.053	-247.501	424.135	-311.590	-263.875	320.473	-359.589	-257.297	292.772	-392.434	-237.787	49.719	-125.351	-263.514	64.181	-181.717	-282.198	93.976	-148.976	-343.280	60.492	-284.486	301.350	1011.891	-263.243	-128.411	1009.589	-303.428	373.098	573.314	-280.000	-60.894	505.051	-328.528	-201.542	556.493	-289.659	227.947	542.683	-296.633	-192.538	101.687	-365.306	459.842	105.702	-321.135	352.527	97.590	-345.057	-299.724	102.303	-308.912	141.411	1812.940	-304.701	-4.476	1814.529	-161.415	1.267	1874.195	-157.913	128.420	1878.785	-196.092	86.956	1554.114	-398.855	81.857	1617.421	-142.512	87.408	1379.767	-424.667	79.002	1190.518	-301.091	316.839	1595.985	-292.832	-130.642	1586.528	-199.618	374.366	955.139	-279.481	409.773	937.555	-246.865	438.372	876.560	-191.814	427.479	893.222	-304.576	402.623	1111.151	-318.118	377.727	1005.830	-261.891	-178.695	1119.116	-282.149	-237.502	1038.869	-271.230	-266.335	864.568	-229.927	-254.510	873.706	-317.949	-228.260	932.580	-227.774	-186.437	948.700	-344.220	374.847	1211.281	-365.030	287.217	1198.954	-375.865	-112.601	1194.149	-328.706	-228.260	1215.862	-327.347	363.636	1438.568	-376.640	335.426	1292.950	-292.899	-190.121	1411.048	-373.004	-192.764	1329.294
6	0.02793	-164.964	232.991	1073.059	-409.542	202.426	1088.831	-408.206	-36.743	1087.813	-178.168	-70.781	1069.258	-207.916	304.673	906.114	-313.074	328.120	876.387	-326.921	336.534	767.989	-230.876	328.337	752.111	-310.215	411.917	439.703	-387.728	390.908	480.103	-386.601	420.016	341.309	-315.502	428.047	355.742	-417.232	400.680	48.567	-138.157	413.474	63.671	-186.406	427.644	87.491	-148.533	500.967	48.385	-320.292	-146.825	844.025	-232.930	-146.713	886.867	-240.171	-164.180	764.686	-318.143	-157.111	747.066	-375.263	-237.278	396.694	-313.469	-247.546	424.144	-311.934	-263.959	320.534	-359.882	-257.289	292.763	-392.447	-237.794	49.714	-125.393	-263.570	64.231	-181.766	-282.300	93.996	-148.965	-343.302	60.484	-283.861	300.805	1011.751	-263.143	-128.604	1009.510	-303.280	372.936	573.292	-280.328	-60.990	505.071	-328.883	-201.573	556.473	-289.566	227.789	542.613	-296.651	-192.645	101.704	-365.298	459.797	105.726	-321.144	352.490	97.612	-345.149	-299.782	102.282	-308.848	141.263	1812.869	-304.712	-4.619	1814.484	-161.463	1.073	1874.238	-157.908	128.245	1878.836	-195.983	86.791	1554.117	-398.727	81.686	1617.351	-142.392	87.202	1379.733	-424.436	78.859	1190.442	-300.932	316.670	1595.959	-292.732	-130.806	1586.520	-199.603	374.263	955.128	-279.504	409.603	937.499	-246.836	438.255	876.523	-191.819	427.399	893.181	-304.513	402.506	1111.089	-318.053	377.574	1005.790	-261.903	-178.818	1119.036	-282.080	-237.623	1038.836	-271.265	-266.454	864.517	-229.952	-254.627	873.660	-317.940	-228.384	932.554	-227.787	-186.585	948.650	-344.198	374.659	1211.242	-364.942	287.044	1198.886	-375.772	-112.746	1194.133	-328.681	-228.414	1215.843	-327.260	363.464	1438.532	-376.558	335.236	1292.921	-292.784	-190.305	1411.040	-372.913	-192.902	1329.284
...

**/

using namespace std;
using namespace MoMa;

TsvParser::TsvParser(string const &fileName, Track *track)
{

    load(fileName, track);
}

void TsvParser::load(string const &fileName, Track *track)
{

    isTimed = false;
    track->clearData(); // Clear the track before

    ifstream tsvFile(fileName.c_str());

    if (!tsvFile.is_open())
    {

        cout << "Track: File could not be opened!" << endl;
        throw std::runtime_error("File could not be opened.");
        return; // We alert on stdout and quit if no file!
    }

    string thisString;
    //Header
    //Line 1: number of frames
    if (tsvFile.good())
        getline(tsvFile, thisLine); //Line 1 (first line)
    thisStream.clear();
    thisStream << thisLine;
    thisStream >> thisString; //Elem 1
    thisStream >> thisString; //Elem 2
    //size_t tab = thisLine.find_last_of("\t");
    //string nframes = thisLine.substr(tab + 1, thisLine.size() -tab -1);
    unsigned int nbOfFrames = atoi(thisString.c_str());

    //Line 3: numer of markers
    if (tsvFile.good())
        getline(tsvFile, thisLine); //Line 2
    if (tsvFile.good())
        getline(tsvFile, thisLine); //Line 3
    //tab = thisLine.find_last_of("\t");
    //string nmarkers = thisLine.substr(tab + 1, thisLine.size() -tab -1);
    thisStream.clear();
    thisStream << thisLine;
    thisStream >> thisString; //Elem 1
    thisStream >> thisString; //Elem 2
    unsigned int nbOfNodes = atoi(thisString.c_str());

    //Line 4: frequency
    if (tsvFile.good())
        getline(tsvFile, thisLine); //Line 4
    //tab = thisLine.find_last_of("\t");
    //string freq = thisLine.substr(tab + 1, thisLine.size() -tab -1);
    thisStream.clear();
    thisStream << thisLine;
    thisStream >> thisString; //Elem 1
    thisStream >> thisString; //Elem 2
    float framerate = atoi(thisString.c_str());

    track->setFrameRate(framerate);

    if (tsvFile.good())
        getline(tsvFile, thisLine); // 5
    if (tsvFile.good())
        getline(tsvFile, thisLine); // 6
    if (tsvFile.good())
        getline(tsvFile, thisLine); // 7
    if (tsvFile.good())
        getline(tsvFile, thisLine); // 8
    if (tsvFile.good())
        getline(tsvFile, thisLine); // 9

    //Line 10: marker names
    if (tsvFile.good())
        getline(tsvFile, thisLine);          // 10
    nodeList = std::make_shared<NodeList>(); // We create a nodeList,
    track->nodeList = nodeList;              // add it to the track
    track->hasNodeList = true;               // and tell everybody
    track->hasRotation = false;
    //track->position.getRefData().resize(3, nbOfNodes, nbOfFrames);
    arma::cube positionData(3, nbOfNodes, nbOfFrames);
    timestamps.resize(nbOfFrames);
    //Remove unwanted delimiters at the end of the line
    while (thisLine[thisLine.size() - 1] == ' ' || thisLine[thisLine.size() - 1] == '\t' || thisLine[thisLine.size() - 1] == '\n')
        thisLine.resize(thisLine.size() - 1);

    thisStream.clear();
    thisStream << thisLine; // We store the line in a string stream

    string tag;
    thisStream >> tag;

    while (thisStream.good())
    {

        // We save the list of tags
        thisStream >> tag;
        rawJoint.push_back(tag);
    }

    //if (rawJoint[rawJoint.size() -1] == rawJoint[rawJoint.size() -2])
    //    rawJoint.resize(rawJoint.size() -1); //(streamstring bug, it repeats last value if there was a tab at the end of the line)

    for (int r = 0, n = 0; n < nbOfNodes; r += 1, n++)
    {

        //track->nodeList->at(n) = rawJoint[r];
        track->nodeList->insert(make_pair(rawJoint[r], n));
    }

    //Check optional line (column headers)
    getline(tsvFile, thisLine);
    stringstream tmpstream;
    string tmpstring;
    tmpstream << thisLine;
    tmpstream >> tmpstring;
    if (tmpstring == "Frame") //optional column (timestamps)
        isTimed = true;
    if (tmpstring == "Frame" || tmpstring == rawJoint[0]) //optional line
        getline(tsvFile, thisLine);

    //Data

    unsigned int frameCpt = 0; // Init frame count

    if (thisLine.substr(0, 2) == "1\t")
    { //if the first line begins with "1  ...", it is timed. So the first to columns are frme number and timestamp

        isTimed = true;
    }

    do
    { //we already extracted first data line in "thisLine"

        if (thisLine != "" && thisLine != " " && thisLine != "\t" && thisLine != "\n")
        {

            checkemptytabs(thisLine);

            arma::mat posMat(3, nbOfNodes);

            thisStream.clear();     // Clear and grab
            thisStream << thisLine; // a new line

            //thisStream >> std::noskipws;
            if (isTimed)
            {

                float ts;
                thisStream >> ts; //frame index
                thisStream >> ts; //timestamp
                timestamps[frameCpt] = ts;
            }

            if (thisStream.good())
            {

                unsigned int nodeCpt = 0;

                for (int k = 0; k < nbOfNodes; k++)
                {

                    string value[12];

                    thisStream >> value[0];
                    thisStream >> value[1];
                    thisStream >> value[2];

                    if (value[0] == "NaN" || atof(value[0].c_str()) > MOMAINF)
                    {

                        // Data are ignored and the matrices
                        // take arma's NaNs as positions/rotations

                        posMat.col(nodeCpt) = arma::ones(3) * arma::datum::nan;
                    }
                    else
                    {

                        posMat(0, nodeCpt) = atof(value[0].c_str());
                        posMat(1, nodeCpt) = atof(value[1].c_str());
                        posMat(2, nodeCpt) = atof(value[2].c_str());

                        /*posMat( axisIndex[k], nodeCpt ) *= 1000;
                        posMat( axisIndex[k+1], nodeCpt ) *= 1000;
                        posMat( axisIndex[k+2], nodeCpt ) *= 1000;*/
                    }
                    nodeCpt++;
                }

                positionData.slice(frameCpt) = posMat; // Put frames at location

                frameCpt++;
            }
        }

        getline(tsvFile, thisLine);

    } while (tsvFile.good());

    //    track->hasOrigNodeRot_as_boneRot=true;

    //track->position.SetValidParam();
    //if (track->hasRotation)
    //    track->rotation.SetValidParam();

    if (!isTimed)
        track->position.setData(framerate, positionData);
    else
        track->position.setData(timestamps, positionData);

    tsvFile.close();
}

void TsvParser::checkemptytabs(std::string &mystring)
{

    if (mystring[0] == '\t')
        mystring.insert(0, "NaN"); //Note supposed to begin with a tab, unless the first value is missing

    size_t found;
    //Replace empty tabs by NaN
    while ((mystring.find("\t\t")) != string::npos)
    {
        found = mystring.find("\t\t");
        mystring.insert(found + 1, "NaN"); //Insert NaN between two tabs
    }

    //Replace whitespaces by NaN
    while ((mystring.find(" ")) != string::npos)
    {
        found = mystring.find(" ");
        mystring.insert(found + 1, "NaN"); //Insert NaN between two tabs
    }
}