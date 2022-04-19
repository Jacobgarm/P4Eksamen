<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="9.6.2">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="ESP32-DEVKITC">
<packages>
<package name="ESP32-DEVKITC">
<pad name="1" x="-22.87" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="2" x="-20.33" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="3" x="-17.79" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="4" x="-15.25" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="5" x="-12.71" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="6" x="-10.17" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="7" x="-7.63" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="8" x="-5.09" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="9" x="-2.55" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="10" x="-0.01" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="11" x="2.53" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="12" x="5.07" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="13" x="7.61" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="14" x="10.15" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="15" x="12.69" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="16" x="15.23" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="17" x="17.77" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="18" x="20.31" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="19" x="22.85" y="-11.42" drill="1" diameter="1.9304"/>
<pad name="38" x="-22.87" y="11.23" drill="1" diameter="1.9304"/>
<pad name="37" x="-20.33" y="11.23" drill="1" diameter="1.9304"/>
<pad name="36" x="-17.79" y="11.23" drill="1" diameter="1.9304"/>
<pad name="35" x="-15.25" y="11.23" drill="1" diameter="1.9304"/>
<pad name="34" x="-12.71" y="11.23" drill="1" diameter="1.9304"/>
<pad name="33" x="-10.17" y="11.23" drill="1" diameter="1.9304"/>
<pad name="32" x="-7.63" y="11.23" drill="1" diameter="1.9304"/>
<pad name="31" x="-5.09" y="11.23" drill="1" diameter="1.9304"/>
<pad name="30" x="-2.55" y="11.23" drill="1" diameter="1.9304"/>
<pad name="29" x="-0.01" y="11.23" drill="1" diameter="1.9304"/>
<pad name="28" x="2.53" y="11.23" drill="1" diameter="1.9304"/>
<pad name="27" x="5.07" y="11.23" drill="1" diameter="1.9304"/>
<pad name="26" x="7.61" y="11.23" drill="1" diameter="1.9304"/>
<pad name="25" x="10.15" y="11.23" drill="1" diameter="1.9304"/>
<pad name="24" x="12.69" y="11.23" drill="1" diameter="1.9304"/>
<pad name="23" x="15.23" y="11.23" drill="1" diameter="1.9304"/>
<pad name="22" x="17.77" y="11.23" drill="1" diameter="1.9304"/>
<pad name="21" x="20.31" y="11.23" drill="1" diameter="1.9304"/>
<pad name="20" x="22.85" y="11.23" drill="1" diameter="1.9304"/>
<wire x1="-22.85" y1="5.86" x2="-22.85" y2="2.02" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="2.02" x2="-17.73" y2="2.02" width="0.4064" layer="21"/>
<wire x1="-17.73" y1="2.02" x2="-17.73" y2="0.74" width="0.4064" layer="21"/>
<wire x1="-17.73" y1="0.74" x2="-22.85" y2="0.74" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="0.74" x2="-22.85" y2="-0.54" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="-0.54" x2="-17.73" y2="-0.54" width="0.4064" layer="21"/>
<wire x1="-17.73" y1="-0.54" x2="-17.73" y2="-1.82" width="0.4064" layer="21"/>
<wire x1="-17.73" y1="-1.82" x2="-22.85" y2="-1.82" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="-1.82" x2="-22.85" y2="-3.1" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="-3.1" x2="-17.73" y2="-3.1" width="0.4064" layer="21"/>
<wire x1="-17.73" y1="-3.1" x2="-17.73" y2="-4.38" width="0.4064" layer="21"/>
<wire x1="-17.73" y1="-4.38" x2="-22.85" y2="-4.38" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="-4.38" x2="-22.85" y2="-5.66" width="0.4064" layer="21"/>
<wire x1="-22.85" y1="-5.66" x2="-15.17" y2="-5.66" width="0.4064" layer="21"/>
<wire x1="-15.17" y1="-5.66" x2="-15.17" y2="0.74" width="0.4064" layer="21"/>
<text x="-22.21" y="-9.5" size="1.016" layer="21" rot="R90">3V3</text>
<text x="-19.67" y="-9.5" size="1.016" layer="21" rot="R90">EN</text>
<text x="-17.13" y="-9.5" size="1.016" layer="21" rot="R90">SVP</text>
<text x="-14.59" y="-9.5" size="1.016" layer="21" rot="R90">SVN</text>
<text x="-12.05" y="-9.5" size="1.016" layer="21" rot="R90">IO34</text>
<text x="-9.51" y="-9.5" size="1.016" layer="21" rot="R90">IO35</text>
<text x="-6.97" y="-9.5" size="1.016" layer="21" rot="R90">IO32</text>
<text x="-4.43" y="-9.5" size="1.016" layer="21" rot="R90">IO33</text>
<text x="-1.89" y="-9.5" size="1.016" layer="21" rot="R90">IO25</text>
<text x="0.65" y="-9.5" size="1.016" layer="21" rot="R90">IO26</text>
<text x="3.19" y="-9.5" size="1.016" layer="21" rot="R90">IO27</text>
<text x="5.73" y="-9.5" size="1.016" layer="21" rot="R90">IO14</text>
<text x="8.27" y="-9.5" size="1.016" layer="21" rot="R90">IO12</text>
<text x="10.81" y="-9.5" size="1.016" layer="21" rot="R90">GND</text>
<text x="13.35" y="-9.5" size="1.016" layer="21" rot="R90">IO13</text>
<text x="15.89" y="-9.5" size="1.016" layer="21" rot="R90">SD2</text>
<text x="18.43" y="-9.5" size="1.016" layer="21" rot="R90">SD3</text>
<text x="20.97" y="-9.5" size="1.016" layer="21" rot="R90">CMD</text>
<text x="23.51" y="-9.5" size="1.016" layer="21" rot="R90">5V</text>
<text x="-22.19" y="6.52" size="1.016" layer="21" rot="R90">GND</text>
<text x="-19.65" y="6.52" size="1.016" layer="21" rot="R90">IO23</text>
<text x="-17.11" y="6.52" size="1.016" layer="21" rot="R90">IO22</text>
<text x="-14.57" y="6.52" size="1.016" layer="21" rot="R90">TXD0</text>
<text x="-12.03" y="6.52" size="1.016" layer="21" rot="R90">RXD0</text>
<text x="-9.49" y="6.52" size="1.016" layer="21" rot="R90">IO21</text>
<text x="-6.95" y="6.52" size="1.016" layer="21" rot="R90">GND</text>
<text x="-4.41" y="6.52" size="1.016" layer="21" rot="R90">IO19</text>
<text x="-1.87" y="6.52" size="1.016" layer="21" rot="R90">IO18</text>
<text x="0.67" y="6.52" size="1.016" layer="21" rot="R90">IO5</text>
<text x="3.21" y="6.52" size="1.016" layer="21" rot="R90">IO17</text>
<text x="5.75" y="6.52" size="1.016" layer="21" rot="R90">IO16</text>
<text x="8.29" y="6.52" size="1.016" layer="21" rot="R90">IO4</text>
<text x="10.83" y="6.52" size="1.016" layer="21" rot="R90">IO0</text>
<text x="13.37" y="6.52" size="1.016" layer="21" rot="R90">IO2</text>
<text x="15.91" y="6.52" size="1.016" layer="21" rot="R90">IO15</text>
<text x="18.45" y="6.52" size="1.016" layer="21" rot="R90">SD1</text>
<text x="20.99" y="6.52" size="1.016" layer="21" rot="R90">SD0</text>
<text x="23.53" y="6.52" size="1.016" layer="21" rot="R90">CLK</text>
<text x="-4.93" y="-1.18" size="1.9304" layer="21">ESP32-DevkitC</text>
<wire x1="-24.13" y1="12.7" x2="24.13" y2="12.7" width="0.254" layer="21"/>
<wire x1="24.13" y1="12.7" x2="24.13" y2="-12.7" width="0.254" layer="21"/>
<wire x1="24.13" y1="-12.7" x2="-24.13" y2="-12.7" width="0.254" layer="21"/>
<wire x1="-24.13" y1="-12.7" x2="-24.13" y2="12.7" width="0.254" layer="21"/>
<text x="-24.13" y="13.97" size="1.27" layer="21">&gt;NAME</text>
<text x="10.16" y="-15.24" size="1.27" layer="27">ESP32-DEVKITC</text>
</package>
</packages>
<symbols>
<symbol name="ESP32-DEVKITC">
<wire x1="-25.4" y1="-12.7" x2="-25.4" y2="12.7" width="0.254" layer="94"/>
<wire x1="-25.4" y1="12.7" x2="25.4" y2="12.7" width="0.254" layer="94"/>
<wire x1="25.4" y1="12.7" x2="25.4" y2="-12.7" width="0.254" layer="94"/>
<wire x1="25.4" y1="-12.7" x2="-25.4" y2="-12.7" width="0.254" layer="94"/>
<pin name="3V3" x="-22.86" y="-17.78" length="middle" rot="R90"/>
<pin name="EN" x="-20.32" y="-17.78" length="middle" rot="R90"/>
<pin name="SVP" x="-17.78" y="-17.78" length="middle" rot="R90"/>
<pin name="SVN" x="-15.24" y="-17.78" length="middle" rot="R90"/>
<pin name="IO34" x="-12.7" y="-17.78" length="middle" rot="R90"/>
<pin name="IO35" x="-10.16" y="-17.78" length="middle" rot="R90"/>
<pin name="IO32" x="-7.62" y="-17.78" length="middle" rot="R90"/>
<pin name="IO33" x="-5.08" y="-17.78" length="middle" rot="R90"/>
<pin name="IO25" x="-2.54" y="-17.78" length="middle" rot="R90"/>
<pin name="IO26" x="0" y="-17.78" length="middle" rot="R90"/>
<pin name="IO27" x="2.54" y="-17.78" length="middle" rot="R90"/>
<pin name="IO14" x="5.08" y="-17.78" length="middle" rot="R90"/>
<pin name="IO12" x="7.62" y="-17.78" length="middle" rot="R90"/>
<pin name="GND@14" x="10.16" y="-17.78" length="middle" rot="R90"/>
<pin name="IO13" x="12.7" y="-17.78" length="middle" rot="R90"/>
<pin name="SD2" x="15.24" y="-17.78" length="middle" rot="R90"/>
<pin name="SD3" x="17.78" y="-17.78" length="middle" rot="R90"/>
<pin name="CMD" x="20.32" y="-17.78" length="middle" rot="R90"/>
<pin name="5V" x="22.86" y="-17.78" length="middle" rot="R90"/>
<pin name="CLK" x="22.86" y="17.78" length="middle" rot="R270"/>
<pin name="SD0" x="20.32" y="17.78" length="middle" rot="R270"/>
<pin name="SD1" x="17.78" y="17.78" length="middle" rot="R270"/>
<pin name="IO15" x="15.24" y="17.78" length="middle" rot="R270"/>
<pin name="IO2" x="12.7" y="17.78" length="middle" rot="R270"/>
<pin name="IO0" x="10.16" y="17.78" length="middle" rot="R270"/>
<pin name="IO4" x="7.62" y="17.78" length="middle" rot="R270"/>
<pin name="IO16" x="5.08" y="17.78" length="middle" rot="R270"/>
<pin name="IO17" x="2.54" y="17.78" length="middle" rot="R270"/>
<pin name="IO5" x="0" y="17.78" length="middle" rot="R270"/>
<pin name="IO18" x="-2.54" y="17.78" length="middle" rot="R270"/>
<pin name="IO19" x="-5.08" y="17.78" length="middle" rot="R270"/>
<pin name="GND@32" x="-7.62" y="17.78" length="middle" rot="R270"/>
<pin name="IO21" x="-10.16" y="17.78" length="middle" rot="R270"/>
<pin name="RXD0" x="-12.7" y="17.78" length="middle" rot="R270"/>
<pin name="TXD0" x="-15.24" y="17.78" length="middle" rot="R270"/>
<pin name="IO22" x="-17.78" y="17.78" length="middle" rot="R270"/>
<pin name="IO23" x="-20.32" y="17.78" length="middle" rot="R270"/>
<pin name="GND@38" x="-22.86" y="17.78" length="middle" rot="R270"/>
<text x="-26.67" y="5.08" size="1.27" layer="95" rot="R90">&gt;NAME</text>
<text x="27.94" y="-12.7" size="1.27" layer="96" rot="R90">ESP32-DEVKITC</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="ESP32DEVKITC">
<gates>
<gate name="G$1" symbol="ESP32-DEVKITC" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ESP32-DEVKITC">
<connects>
<connect gate="G$1" pin="3V3" pad="1"/>
<connect gate="G$1" pin="5V" pad="19"/>
<connect gate="G$1" pin="CLK" pad="20"/>
<connect gate="G$1" pin="CMD" pad="18"/>
<connect gate="G$1" pin="EN" pad="2"/>
<connect gate="G$1" pin="GND@14" pad="14"/>
<connect gate="G$1" pin="GND@32" pad="32"/>
<connect gate="G$1" pin="GND@38" pad="38"/>
<connect gate="G$1" pin="IO0" pad="25"/>
<connect gate="G$1" pin="IO12" pad="13"/>
<connect gate="G$1" pin="IO13" pad="15"/>
<connect gate="G$1" pin="IO14" pad="12"/>
<connect gate="G$1" pin="IO15" pad="23"/>
<connect gate="G$1" pin="IO16" pad="27"/>
<connect gate="G$1" pin="IO17" pad="28"/>
<connect gate="G$1" pin="IO18" pad="30"/>
<connect gate="G$1" pin="IO19" pad="31"/>
<connect gate="G$1" pin="IO2" pad="24"/>
<connect gate="G$1" pin="IO21" pad="33"/>
<connect gate="G$1" pin="IO22" pad="36"/>
<connect gate="G$1" pin="IO23" pad="37"/>
<connect gate="G$1" pin="IO25" pad="9"/>
<connect gate="G$1" pin="IO26" pad="10"/>
<connect gate="G$1" pin="IO27" pad="11"/>
<connect gate="G$1" pin="IO32" pad="7"/>
<connect gate="G$1" pin="IO33" pad="8"/>
<connect gate="G$1" pin="IO34" pad="5"/>
<connect gate="G$1" pin="IO35" pad="6"/>
<connect gate="G$1" pin="IO4" pad="26"/>
<connect gate="G$1" pin="IO5" pad="29"/>
<connect gate="G$1" pin="RXD0" pad="34"/>
<connect gate="G$1" pin="SD0" pad="21"/>
<connect gate="G$1" pin="SD1" pad="22"/>
<connect gate="G$1" pin="SD2" pad="16"/>
<connect gate="G$1" pin="SD3" pad="17"/>
<connect gate="G$1" pin="SVN" pad="4"/>
<connect gate="G$1" pin="SVP" pad="3"/>
<connect gate="G$1" pin="TXD0" pad="35"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="tftdisplay">
<packages>
<package name="FOOT_TFT">
<rectangle x1="-10.16" y1="-3.81" x2="11.43" y2="5.08" layer="21"/>
<pad name="P$1" x="-7.62" y="3.81" drill="0.6" shape="square"/>
<pad name="P$2" x="1.27" y="3.81" drill="0.6" shape="square"/>
<pad name="P$3" x="-3.81" y="0" drill="0.6" shape="square"/>
<pad name="P$4" x="3.81" y="2.54" drill="0.6" shape="square"/>
<pad name="P$5" x="8.89" y="0" drill="0.6" shape="square"/>
<pad name="P$6" x="2.54" y="-1.27" drill="0.6" shape="square"/>
<text x="-5.08" y="-1.27" size="1.27" layer="21">Cool</text>
<text x="-3.81" y="1.27" size="1.27" layer="21">Cool</text>
<text x="-5.08" y="2.54" size="1.27" layer="21">Cool</text>
<text x="-10.16" y="0" size="1.27" layer="21">Cool</text>
<text x="-10.16" y="3.81" size="1.27" layer="21">Cool</text>
<text x="-7.62" y="2.54" size="1.27" layer="21">Cool</text>
<text x="-5.08" y="2.54" size="1.27" layer="21">Cool</text>
<text x="-1.27" y="1.27" size="1.27" layer="21">Cool</text>
<text x="8.89" y="-1.27" size="1.27" layer="21">Cool</text>
<text x="15.24" y="2.54" size="1.27" layer="21">Cool</text>
<text x="-16.51" y="1.27" size="1.27" layer="21">Cool</text>
<text x="0" y="6.35" size="1.27" layer="21">Cool</text>
<text x="-1.27" y="-7.62" size="1.27" layer="21">Cool</text>
<pad name="P$7" x="-6.35" y="1.27" drill="0.6" shape="square"/>
<pad name="P$8" x="-3.81" y="3.81" drill="0.6" shape="square"/>
<pad name="P$9" x="-6.35" y="-1.27" drill="0.6" shape="square"/>
<pad name="P$10" x="-1.27" y="2.54" drill="0.6" shape="square"/>
<pad name="P$11" x="-2.54" y="-2.54" drill="0.6" shape="square"/>
<pad name="P$12" x="6.35" y="-2.54" drill="0.6" shape="square"/>
<pad name="P$13" x="7.62" y="2.54" drill="0.6" shape="square"/>
<pad name="P$14" x="10.16" y="3.81" drill="0.6" shape="square"/>
<pad name="P$15" x="5.08" y="0" drill="0.6" shape="square"/>
<pad name="P$16" x="1.27" y="1.27" drill="0.6" shape="square"/>
<pad name="P$17" x="0" y="-2.54" drill="0.6" shape="square"/>
<pad name="P$18" x="-1.27" y="0" drill="0.6" shape="square"/>
</package>
</packages>
<symbols>
<symbol name="SYM_TFT">
<wire x1="-73.66" y1="17.78" x2="-73.66" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-73.66" y1="-20.32" x2="-7.62" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-20.32" x2="-7.62" y2="17.78" width="0.254" layer="94"/>
<wire x1="-7.62" y1="17.78" x2="-73.66" y2="17.78" width="0.254" layer="94"/>
<pin name="T_IRQ" x="-78.74" y="15.24" length="middle"/>
<pin name="T_D0" x="-78.74" y="12.7" length="middle"/>
<pin name="T_DIN" x="-78.74" y="10.16" length="middle"/>
<pin name="T_CD" x="-78.74" y="7.62" length="middle"/>
<pin name="T_CLK" x="-78.74" y="5.08" length="middle"/>
<pin name="SDO" x="-78.74" y="2.54" length="middle"/>
<pin name="LED" x="-78.74" y="0" length="middle"/>
<pin name="CDK" x="-78.74" y="-2.54" length="middle"/>
<pin name="SDI" x="-78.74" y="-5.08" length="middle"/>
<pin name="DC" x="-78.74" y="-7.62" length="middle"/>
<pin name="RESET" x="-78.74" y="-10.16" length="middle"/>
<pin name="CS" x="-78.74" y="-12.7" length="middle"/>
<pin name="GND" x="-78.74" y="-15.24" length="middle"/>
<pin name="VCC" x="-78.74" y="-17.78" length="middle"/>
<pin name="SD_CS" x="-2.54" y="-5.08" length="middle" rot="R180"/>
<pin name="SD_MOSI" x="-2.54" y="-2.54" length="middle" rot="R180"/>
<pin name="SD_MISO" x="-2.54" y="0" length="middle" rot="R180"/>
<pin name="SD_SCK" x="-2.54" y="2.54" length="middle" rot="R180"/>
<text x="-45.72" y="-25.4" size="1.778" layer="95">&gt; NAME</text>
<text x="-45.72" y="-30.48" size="1.778" layer="96">&gt; VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="TFT">
<gates>
<gate name="G$1" symbol="SYM_TFT" x="43.18" y="2.54"/>
</gates>
<devices>
<device name="" package="FOOT_TFT">
<connects>
<connect gate="G$1" pin="CDK" pad="P$1"/>
<connect gate="G$1" pin="CS" pad="P$2"/>
<connect gate="G$1" pin="DC" pad="P$3"/>
<connect gate="G$1" pin="GND" pad="P$4"/>
<connect gate="G$1" pin="LED" pad="P$5"/>
<connect gate="G$1" pin="RESET" pad="P$6"/>
<connect gate="G$1" pin="SDI" pad="P$7"/>
<connect gate="G$1" pin="SDO" pad="P$8"/>
<connect gate="G$1" pin="SD_CS" pad="P$9"/>
<connect gate="G$1" pin="SD_MISO" pad="P$10"/>
<connect gate="G$1" pin="SD_MOSI" pad="P$11"/>
<connect gate="G$1" pin="SD_SCK" pad="P$12"/>
<connect gate="G$1" pin="T_CD" pad="P$13"/>
<connect gate="G$1" pin="T_CLK" pad="P$14"/>
<connect gate="G$1" pin="T_D0" pad="P$15"/>
<connect gate="G$1" pin="T_DIN" pad="P$16"/>
<connect gate="G$1" pin="T_IRQ" pad="P$17"/>
<connect gate="G$1" pin="VCC" pad="P$18"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="Texas Instruments_By_element14_Batch_1">
<description>Developed by element14 :&lt;br&gt;
element14 CAD Library consolidation.ulp
at 30/07/2012 17:45:58</description>
<packages>
<package name="SOP65P640X120-29N">
<smd name="1" x="-2.921" y="4.2164" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="2" x="-2.921" y="3.5814" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="3" x="-2.921" y="2.921" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="4" x="-2.921" y="2.286" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="5" x="-2.921" y="1.6256" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="6" x="-2.921" y="0.9652" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="7" x="-2.921" y="0.3302" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="8" x="-2.921" y="-0.3302" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="9" x="-2.921" y="-0.9652" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="10" x="-2.921" y="-1.6256" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="11" x="-2.921" y="-2.286" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="12" x="-2.921" y="-2.921" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="13" x="-2.921" y="-3.5814" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="14" x="-2.921" y="-4.2164" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="15" x="2.921" y="-4.2164" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="16" x="2.921" y="-3.5814" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="17" x="2.921" y="-2.921" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="18" x="2.921" y="-2.286" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="19" x="2.921" y="-1.6256" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="20" x="2.921" y="-0.9652" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="21" x="2.921" y="-0.3302" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="22" x="2.921" y="0.3302" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="23" x="2.921" y="0.9652" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="24" x="2.921" y="1.6256" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="25" x="2.921" y="2.286" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="26" x="2.921" y="2.921" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="27" x="2.921" y="3.5814" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="28" x="2.921" y="4.2164" dx="1.4732" dy="0.3556" layer="1"/>
<smd name="29" x="0" y="0" dx="2.3876" dy="6.1722" layer="1"/>
<wire x1="-2.2606" y1="4.064" x2="-2.2606" y2="4.3688" width="0" layer="51"/>
<wire x1="-2.2606" y1="4.3688" x2="-3.302" y2="4.3688" width="0" layer="51"/>
<wire x1="-3.302" y1="4.3688" x2="-3.302" y2="4.064" width="0" layer="51"/>
<wire x1="-3.302" y1="4.064" x2="-2.2606" y2="4.064" width="0" layer="51"/>
<wire x1="-2.2606" y1="3.429" x2="-2.2606" y2="3.7338" width="0" layer="51"/>
<wire x1="-2.2606" y1="3.7338" x2="-3.302" y2="3.7338" width="0" layer="51"/>
<wire x1="-3.302" y1="3.7338" x2="-3.302" y2="3.429" width="0" layer="51"/>
<wire x1="-3.302" y1="3.429" x2="-2.2606" y2="3.429" width="0" layer="51"/>
<wire x1="-2.2606" y1="2.7686" x2="-2.2606" y2="3.0734" width="0" layer="51"/>
<wire x1="-2.2606" y1="3.0734" x2="-3.302" y2="3.0734" width="0" layer="51"/>
<wire x1="-3.302" y1="3.0734" x2="-3.302" y2="2.7686" width="0" layer="51"/>
<wire x1="-3.302" y1="2.7686" x2="-2.2606" y2="2.7686" width="0" layer="51"/>
<wire x1="-2.2606" y1="2.1336" x2="-2.2606" y2="2.4384" width="0" layer="51"/>
<wire x1="-2.2606" y1="2.4384" x2="-3.302" y2="2.4384" width="0" layer="51"/>
<wire x1="-3.302" y1="2.4384" x2="-3.302" y2="2.1336" width="0" layer="51"/>
<wire x1="-3.302" y1="2.1336" x2="-2.2606" y2="2.1336" width="0" layer="51"/>
<wire x1="-2.2606" y1="1.4732" x2="-2.2606" y2="1.778" width="0" layer="51"/>
<wire x1="-2.2606" y1="1.778" x2="-3.302" y2="1.778" width="0" layer="51"/>
<wire x1="-3.302" y1="1.778" x2="-3.302" y2="1.4732" width="0" layer="51"/>
<wire x1="-3.302" y1="1.4732" x2="-2.2606" y2="1.4732" width="0" layer="51"/>
<wire x1="-2.2606" y1="0.8128" x2="-2.2606" y2="1.1176" width="0" layer="51"/>
<wire x1="-2.2606" y1="1.1176" x2="-3.302" y2="1.1176" width="0" layer="51"/>
<wire x1="-3.302" y1="1.1176" x2="-3.302" y2="0.8128" width="0" layer="51"/>
<wire x1="-3.302" y1="0.8128" x2="-2.2606" y2="0.8128" width="0" layer="51"/>
<wire x1="-2.2606" y1="0.1778" x2="-2.2606" y2="0.4826" width="0" layer="51"/>
<wire x1="-2.2606" y1="0.4826" x2="-3.302" y2="0.4826" width="0" layer="51"/>
<wire x1="-3.302" y1="0.4826" x2="-3.302" y2="0.1778" width="0" layer="51"/>
<wire x1="-3.302" y1="0.1778" x2="-2.2606" y2="0.1778" width="0" layer="51"/>
<wire x1="-2.2606" y1="-0.4826" x2="-2.2606" y2="-0.1778" width="0" layer="51"/>
<wire x1="-2.2606" y1="-0.1778" x2="-3.302" y2="-0.1778" width="0" layer="51"/>
<wire x1="-3.302" y1="-0.1778" x2="-3.302" y2="-0.4826" width="0" layer="51"/>
<wire x1="-3.302" y1="-0.4826" x2="-2.2606" y2="-0.4826" width="0" layer="51"/>
<wire x1="-2.2606" y1="-1.1176" x2="-2.2606" y2="-0.8128" width="0" layer="51"/>
<wire x1="-2.2606" y1="-0.8128" x2="-3.302" y2="-0.8128" width="0" layer="51"/>
<wire x1="-3.302" y1="-0.8128" x2="-3.302" y2="-1.1176" width="0" layer="51"/>
<wire x1="-3.302" y1="-1.1176" x2="-2.2606" y2="-1.1176" width="0" layer="51"/>
<wire x1="-2.2606" y1="-1.778" x2="-2.2606" y2="-1.4732" width="0" layer="51"/>
<wire x1="-2.2606" y1="-1.4732" x2="-3.302" y2="-1.4732" width="0" layer="51"/>
<wire x1="-3.302" y1="-1.4732" x2="-3.302" y2="-1.778" width="0" layer="51"/>
<wire x1="-3.302" y1="-1.778" x2="-2.2606" y2="-1.778" width="0" layer="51"/>
<wire x1="-2.2606" y1="-2.4384" x2="-2.2606" y2="-2.1336" width="0" layer="51"/>
<wire x1="-2.2606" y1="-2.1336" x2="-3.302" y2="-2.1336" width="0" layer="51"/>
<wire x1="-3.302" y1="-2.1336" x2="-3.302" y2="-2.4384" width="0" layer="51"/>
<wire x1="-3.302" y1="-2.4384" x2="-2.2606" y2="-2.4384" width="0" layer="51"/>
<wire x1="-2.2606" y1="-3.0734" x2="-2.2606" y2="-2.7686" width="0" layer="51"/>
<wire x1="-2.2606" y1="-2.7686" x2="-3.302" y2="-2.7686" width="0" layer="51"/>
<wire x1="-3.302" y1="-2.7686" x2="-3.302" y2="-3.0734" width="0" layer="51"/>
<wire x1="-3.302" y1="-3.0734" x2="-2.2606" y2="-3.0734" width="0" layer="51"/>
<wire x1="-2.2606" y1="-3.7338" x2="-2.2606" y2="-3.429" width="0" layer="51"/>
<wire x1="-2.2606" y1="-3.429" x2="-3.302" y2="-3.429" width="0" layer="51"/>
<wire x1="-3.302" y1="-3.429" x2="-3.302" y2="-3.7338" width="0" layer="51"/>
<wire x1="-3.302" y1="-3.7338" x2="-2.2606" y2="-3.7338" width="0" layer="51"/>
<wire x1="-2.2606" y1="-4.3688" x2="-2.2606" y2="-4.064" width="0" layer="51"/>
<wire x1="-2.2606" y1="-4.064" x2="-3.302" y2="-4.064" width="0" layer="51"/>
<wire x1="-3.302" y1="-4.064" x2="-3.302" y2="-4.3688" width="0" layer="51"/>
<wire x1="-3.302" y1="-4.3688" x2="-2.2606" y2="-4.3688" width="0" layer="51"/>
<wire x1="2.2606" y1="-4.064" x2="2.2606" y2="-4.3688" width="0" layer="51"/>
<wire x1="2.2606" y1="-4.3688" x2="3.302" y2="-4.3688" width="0" layer="51"/>
<wire x1="3.302" y1="-4.3688" x2="3.302" y2="-4.064" width="0" layer="51"/>
<wire x1="3.302" y1="-4.064" x2="2.2606" y2="-4.064" width="0" layer="51"/>
<wire x1="2.2606" y1="-3.429" x2="2.2606" y2="-3.7338" width="0" layer="51"/>
<wire x1="2.2606" y1="-3.7338" x2="3.302" y2="-3.7338" width="0" layer="51"/>
<wire x1="3.302" y1="-3.7338" x2="3.302" y2="-3.429" width="0" layer="51"/>
<wire x1="3.302" y1="-3.429" x2="2.2606" y2="-3.429" width="0" layer="51"/>
<wire x1="2.2606" y1="-2.7686" x2="2.2606" y2="-3.0734" width="0" layer="51"/>
<wire x1="2.2606" y1="-3.0734" x2="3.302" y2="-3.0734" width="0" layer="51"/>
<wire x1="3.302" y1="-3.0734" x2="3.302" y2="-2.7686" width="0" layer="51"/>
<wire x1="3.302" y1="-2.7686" x2="2.2606" y2="-2.7686" width="0" layer="51"/>
<wire x1="2.2606" y1="-2.1336" x2="2.2606" y2="-2.4384" width="0" layer="51"/>
<wire x1="2.2606" y1="-2.4384" x2="3.302" y2="-2.4384" width="0" layer="51"/>
<wire x1="3.302" y1="-2.4384" x2="3.302" y2="-2.1336" width="0" layer="51"/>
<wire x1="3.302" y1="-2.1336" x2="2.2606" y2="-2.1336" width="0" layer="51"/>
<wire x1="2.2606" y1="-1.4732" x2="2.2606" y2="-1.778" width="0" layer="51"/>
<wire x1="2.2606" y1="-1.778" x2="3.302" y2="-1.778" width="0" layer="51"/>
<wire x1="3.302" y1="-1.778" x2="3.302" y2="-1.4732" width="0" layer="51"/>
<wire x1="3.302" y1="-1.4732" x2="2.2606" y2="-1.4732" width="0" layer="51"/>
<wire x1="2.2606" y1="-0.8128" x2="2.2606" y2="-1.1176" width="0" layer="51"/>
<wire x1="2.2606" y1="-1.1176" x2="3.302" y2="-1.1176" width="0" layer="51"/>
<wire x1="3.302" y1="-1.1176" x2="3.302" y2="-0.8128" width="0" layer="51"/>
<wire x1="3.302" y1="-0.8128" x2="2.2606" y2="-0.8128" width="0" layer="51"/>
<wire x1="2.2606" y1="-0.1778" x2="2.2606" y2="-0.4826" width="0" layer="51"/>
<wire x1="2.2606" y1="-0.4826" x2="3.302" y2="-0.4826" width="0" layer="51"/>
<wire x1="3.302" y1="-0.4826" x2="3.302" y2="-0.1778" width="0" layer="51"/>
<wire x1="3.302" y1="-0.1778" x2="2.2606" y2="-0.1778" width="0" layer="51"/>
<wire x1="2.2606" y1="0.4826" x2="2.2606" y2="0.1778" width="0" layer="51"/>
<wire x1="2.2606" y1="0.1778" x2="3.302" y2="0.1778" width="0" layer="51"/>
<wire x1="3.302" y1="0.1778" x2="3.302" y2="0.4826" width="0" layer="51"/>
<wire x1="3.302" y1="0.4826" x2="2.2606" y2="0.4826" width="0" layer="51"/>
<wire x1="2.2606" y1="1.1176" x2="2.2606" y2="0.8128" width="0" layer="51"/>
<wire x1="2.2606" y1="0.8128" x2="3.302" y2="0.8128" width="0" layer="51"/>
<wire x1="3.302" y1="0.8128" x2="3.302" y2="1.1176" width="0" layer="51"/>
<wire x1="3.302" y1="1.1176" x2="2.2606" y2="1.1176" width="0" layer="51"/>
<wire x1="2.2606" y1="1.778" x2="2.2606" y2="1.4732" width="0" layer="51"/>
<wire x1="2.2606" y1="1.4732" x2="3.302" y2="1.4732" width="0" layer="51"/>
<wire x1="3.302" y1="1.4732" x2="3.302" y2="1.778" width="0" layer="51"/>
<wire x1="3.302" y1="1.778" x2="2.2606" y2="1.778" width="0" layer="51"/>
<wire x1="2.2606" y1="2.4384" x2="2.2606" y2="2.1336" width="0" layer="51"/>
<wire x1="2.2606" y1="2.1336" x2="3.302" y2="2.1336" width="0" layer="51"/>
<wire x1="3.302" y1="2.1336" x2="3.302" y2="2.4384" width="0" layer="51"/>
<wire x1="3.302" y1="2.4384" x2="2.2606" y2="2.4384" width="0" layer="51"/>
<wire x1="2.2606" y1="3.0734" x2="2.2606" y2="2.7686" width="0" layer="51"/>
<wire x1="2.2606" y1="2.7686" x2="3.302" y2="2.7686" width="0" layer="51"/>
<wire x1="3.302" y1="2.7686" x2="3.302" y2="3.0734" width="0" layer="51"/>
<wire x1="3.302" y1="3.0734" x2="2.2606" y2="3.0734" width="0" layer="51"/>
<wire x1="2.2606" y1="3.7338" x2="2.2606" y2="3.429" width="0" layer="51"/>
<wire x1="2.2606" y1="3.429" x2="3.302" y2="3.429" width="0" layer="51"/>
<wire x1="3.302" y1="3.429" x2="3.302" y2="3.7338" width="0" layer="51"/>
<wire x1="3.302" y1="3.7338" x2="2.2606" y2="3.7338" width="0" layer="51"/>
<wire x1="2.2606" y1="4.3688" x2="2.2606" y2="4.064" width="0" layer="51"/>
<wire x1="2.2606" y1="4.064" x2="3.302" y2="4.064" width="0" layer="51"/>
<wire x1="3.302" y1="4.064" x2="3.302" y2="4.3688" width="0" layer="51"/>
<wire x1="3.302" y1="4.3688" x2="2.2606" y2="4.3688" width="0" layer="51"/>
<wire x1="-2.2606" y1="-4.9022" x2="2.2606" y2="-4.9022" width="0" layer="51"/>
<wire x1="2.2606" y1="-4.9022" x2="2.2606" y2="4.9022" width="0" layer="51"/>
<wire x1="2.2606" y1="4.9022" x2="0.3048" y2="4.9022" width="0" layer="51"/>
<wire x1="0.3048" y1="4.9022" x2="-0.3048" y2="4.9022" width="0" layer="51"/>
<wire x1="-0.3048" y1="4.9022" x2="-2.2606" y2="4.9022" width="0" layer="51"/>
<wire x1="-2.2606" y1="4.9022" x2="-2.2606" y2="-4.9022" width="0" layer="51"/>
<wire x1="0.3048" y1="4.9022" x2="-0.3048" y2="4.9022" width="0" layer="51" curve="-180"/>
<text x="-3.7592" y="4.445" size="1.27" layer="51" ratio="6" rot="SR0">*</text>
<wire x1="-4.953" y1="-1.6256" x2="-3.9624" y2="-1.6256" width="0.1524" layer="21"/>
<wire x1="3.9624" y1="-0.9906" x2="5.0038" y2="-0.9906" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="4.7244" x2="2.2606" y2="4.9022" width="0.1524" layer="21"/>
<wire x1="-2.2606" y1="-4.7244" x2="-2.2606" y2="-4.9022" width="0.1524" layer="21"/>
<wire x1="-2.2606" y1="-4.9022" x2="2.2606" y2="-4.9022" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="-4.9022" x2="2.2606" y2="-4.7244" width="0.1524" layer="21"/>
<wire x1="2.2606" y1="4.9022" x2="0.3048" y2="4.9022" width="0.1524" layer="21"/>
<wire x1="0.3048" y1="4.9022" x2="-0.3048" y2="4.9022" width="0.1524" layer="21"/>
<wire x1="-0.3048" y1="4.9022" x2="-2.2606" y2="4.9022" width="0.1524" layer="21"/>
<wire x1="-2.2606" y1="4.9022" x2="-2.2606" y2="4.7244" width="0.1524" layer="21"/>
<wire x1="0.3048" y1="4.9022" x2="-0.3048" y2="4.9022" width="0.1524" layer="21" curve="-180"/>
<text x="-3.7592" y="4.445" size="1.27" layer="21" ratio="6" rot="SR0">*</text>
<text x="-3.4544" y="5.715" size="2.0828" layer="25" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-3.4544" y="-7.62" size="2.0828" layer="27" ratio="10" rot="SR0">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="DRV8824PWPR">
<pin name="VMA" x="-17.78" y="22.86" length="middle" direction="pwr"/>
<pin name="VMB" x="-17.78" y="20.32" length="middle" direction="pwr"/>
<pin name="AVREF" x="-17.78" y="17.78" length="middle" direction="in"/>
<pin name="BVREF" x="-17.78" y="15.24" length="middle" direction="in"/>
<pin name="NHOME" x="-17.78" y="10.16" length="middle" direction="in"/>
<pin name="NRESET" x="-17.78" y="7.62" length="middle" direction="in"/>
<pin name="NSLEEP" x="-17.78" y="5.08" length="middle" direction="in"/>
<pin name="DECAY" x="-17.78" y="2.54" length="middle" direction="in"/>
<pin name="NENBL" x="-17.78" y="0" length="middle" direction="in"/>
<pin name="DIR" x="-17.78" y="-2.54" length="middle" direction="in"/>
<pin name="STEP" x="-17.78" y="-5.08" length="middle" direction="in"/>
<pin name="MODE0" x="-17.78" y="-10.16" length="middle" direction="in"/>
<pin name="MODE1" x="-17.78" y="-12.7" length="middle" direction="in"/>
<pin name="MODE2" x="-17.78" y="-15.24" length="middle" direction="in"/>
<pin name="NC" x="-17.78" y="-20.32" length="middle" direction="nc"/>
<pin name="GND_2" x="-17.78" y="-25.4" length="middle" direction="pas"/>
<pin name="GND" x="-17.78" y="-27.94" length="middle" direction="pas"/>
<pin name="EPAD" x="-17.78" y="-30.48" length="middle" direction="pas"/>
<pin name="AOUT1" x="17.78" y="22.86" length="middle" direction="out" rot="R180"/>
<pin name="AOUT2" x="17.78" y="20.32" length="middle" direction="out" rot="R180"/>
<pin name="BOUT1" x="17.78" y="17.78" length="middle" direction="out" rot="R180"/>
<pin name="BOUT2" x="17.78" y="15.24" length="middle" direction="out" rot="R180"/>
<pin name="ISENA" x="17.78" y="12.7" length="middle" rot="R180"/>
<pin name="ISENB" x="17.78" y="10.16" length="middle" rot="R180"/>
<pin name="VCP" x="17.78" y="7.62" length="middle" rot="R180"/>
<pin name="CP1" x="17.78" y="5.08" length="middle" rot="R180"/>
<pin name="CP2" x="17.78" y="2.54" length="middle" rot="R180"/>
<pin name="NFAULT" x="17.78" y="0" length="middle" direction="out" rot="R180"/>
<pin name="V3P3OUT" x="17.78" y="-2.54" length="middle" direction="out" rot="R180"/>
<wire x1="-12.7" y1="27.94" x2="-12.7" y2="-35.56" width="0.4064" layer="94"/>
<wire x1="-12.7" y1="-35.56" x2="12.7" y2="-35.56" width="0.4064" layer="94"/>
<wire x1="12.7" y1="-35.56" x2="12.7" y2="27.94" width="0.4064" layer="94"/>
<wire x1="12.7" y1="27.94" x2="-12.7" y2="27.94" width="0.4064" layer="94"/>
<text x="-5.3594" y="31.9786" size="2.0828" layer="95" ratio="10" rot="SR0">&gt;NAME</text>
<text x="-3.556" y="-40.5892" size="2.0828" layer="96" ratio="10" rot="SR0">&gt;VALUE</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="DRV8824PWPR" prefix="U">
<description>STEPPER MOTOR CONTROLLER IC</description>
<gates>
<gate name="A" symbol="DRV8824PWPR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SOP65P640X120-29N">
<connects>
<connect gate="A" pin="AOUT1" pad="5"/>
<connect gate="A" pin="AOUT2" pad="7"/>
<connect gate="A" pin="AVREF" pad="12"/>
<connect gate="A" pin="BOUT1" pad="10"/>
<connect gate="A" pin="BOUT2" pad="8"/>
<connect gate="A" pin="BVREF" pad="13"/>
<connect gate="A" pin="CP1" pad="1"/>
<connect gate="A" pin="CP2" pad="2"/>
<connect gate="A" pin="DECAY" pad="19"/>
<connect gate="A" pin="DIR" pad="20"/>
<connect gate="A" pin="EPAD" pad="29"/>
<connect gate="A" pin="GND" pad="28"/>
<connect gate="A" pin="GND_2" pad="14"/>
<connect gate="A" pin="ISENA" pad="6"/>
<connect gate="A" pin="ISENB" pad="9"/>
<connect gate="A" pin="MODE0" pad="24"/>
<connect gate="A" pin="MODE1" pad="25"/>
<connect gate="A" pin="MODE2" pad="26"/>
<connect gate="A" pin="NC" pad="23"/>
<connect gate="A" pin="NENBL" pad="21"/>
<connect gate="A" pin="NFAULT" pad="18"/>
<connect gate="A" pin="NHOME" pad="27"/>
<connect gate="A" pin="NRESET" pad="16"/>
<connect gate="A" pin="NSLEEP" pad="17"/>
<connect gate="A" pin="STEP" pad="22"/>
<connect gate="A" pin="V3P3OUT" pad="15"/>
<connect gate="A" pin="VCP" pad="3"/>
<connect gate="A" pin="VMA" pad="4"/>
<connect gate="A" pin="VMB" pad="11"/>
</connects>
<technologies>
<technology name="">
<attribute name="MPN" value="DRV8824PWPR" constant="no"/>
<attribute name="OC_FARNELL" value="-" constant="no"/>
<attribute name="OC_NEWARK" value="74R6336" constant="no"/>
<attribute name="PACKAGE" value="TSSOP-28" constant="no"/>
<attribute name="SUPPLIER" value="Texas Instruments" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<modules>
<module name="TFT" prefix="" dx="30.48" dy="20.32">
<ports>
</ports>
<variantdefs>
</variantdefs>
<parts>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</module>
</modules>
<parts>
<part name="U$1" library="ESP32-DEVKITC" deviceset="ESP32DEVKITC" device=""/>
<part name="U$2" library="tftdisplay" deviceset="TFT" device=""/>
<part name="U1" library="Texas Instruments_By_element14_Batch_1" deviceset="DRV8824PWPR" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="53.34" y="35.56" smashed="yes" rot="R90">
<attribute name="NAME" x="48.26" y="8.89" size="1.27" layer="95" rot="R180"/>
</instance>
<instance part="U$2" gate="G$1" x="190.5" y="33.02" smashed="yes"/>
<instance part="U1" gate="A" x="81.28" y="-35.56" smashed="yes">
<attribute name="NAME" x="75.9206" y="-3.5814" size="2.0828" layer="95" ratio="10" rot="SR0"/>
<attribute name="VALUE" x="77.724" y="-76.1492" size="2.0828" layer="96" ratio="10" rot="SR0"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="GND@38"/>
<wire x1="35.56" y1="12.7" x2="22.86" y2="12.7" width="0.1524" layer="91"/>
<label x="22.86" y="12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="3.3V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="3V3"/>
<wire x1="71.12" y1="12.7" x2="76.2" y2="12.7" width="0.1524" layer="91"/>
<label x="76.2" y="12.7" size="1.778" layer="95"/>
</segment>
</net>
<net name="5V" class="0">
<segment>
<pinref part="U$1" gate="G$1" pin="5V"/>
<wire x1="71.12" y1="58.42" x2="78.74" y2="58.42" width="0.1524" layer="91"/>
<label x="78.74" y="58.42" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
