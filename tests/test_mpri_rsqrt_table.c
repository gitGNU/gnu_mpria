/* tests/test_mpri_rsqrt_table.c -- C input file */
/*
 * MPRIA - GNU Multi-Precision Rational Interval Arithmetic Library
 * Copyright (C) 2009-2016  Jerome Benoit <jgmbenoit@rezozer.net>
 *
 * This file is part of the GNU MPRIA Library.
 *
 * The GNU MPRIA Library is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The GNU MPRIA Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the GNU MPRIA Library.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * generation date: 2016/01/21 21:19:47 UTC
 * generation place: NeN
 * generated with: test_mpri_rsqrt_table.cg (GAP 4.7.5)
 * generated by: jgmb <jgmb@NeN>
 *
 * comment: not human readable
 *
 */

test_mpri_rsqrt_tuple test_table[]={
	{"2","3",10,"56/97","169/239"},
	{"2","3",24,"10864/18817","33461/47321"},
	{"2","3",53,"408855776/708158977","1311738121/1855077841"},
	{"2","3",113,"579069776145402304/1002978273411373057","2015874949414289041/2850877693509864481"},
	{"2","3",256,"840988692965369018725894635609587643345/1456635144806962003478307594875799733226","942650270102046130733437746596776286089/1333108796552974910559500626578123263279"},
	{"2","3",512,"175904051126398795124225065599735844105435698140531518180617524377976332996976/304674753808116112624040985753062133503991980989291507854188532268249934395777","1041047392601691174994137053990036552026091093097599958300955916086130355212021/1472263341690459751560022662071732344879659802345870466465594433532459189239641"},
	{"2","3",1024,"28720682667070963357924534322680015958968211660576346032633829680779466301631669358754238715055432912645437236197396265290926753299271695767364548361813951/49745681607429718634264588390953119759762323895917021547650382985744292497677614587570656266585962872861953341569673699669394815137245018415617591532712802","37377269190167522339457370469648760903867691713248359781530654205930946101551198857017808314217921196177539741081431327359978396389819954978801148797109325/52859441013204941216977989165824362837993054019925908927384477194798606179162062866795656036760758841784961286215917321059991272827351929193004525102909193"},
	{"1/3","1/2",10,"239/169","97/56"},
	{"1/3","1/2",24,"47321/33461","18817/10864"},
	{"1/3","1/2",53,"1855077841/1311738121","708158977/408855776"},
	{"1/3","1/2",113,"2850877693509864481/2015874949414289041","1002978273411373057/579069776145402304"},
	{"1/3","1/2",256,"1333108796552974910559500626578123263279/942650270102046130733437746596776286089","1456635144806962003478307594875799733226/840988692965369018725894635609587643345"},
	{"1/3","1/2",512,"1472263341690459751560022662071732344879659802345870466465594433532459189239641/1041047392601691174994137053990036552026091093097599958300955916086130355212021","304674753808116112624040985753062133503991980989291507854188532268249934395777/175904051126398795124225065599735844105435698140531518180617524377976332996976"},
	{"1/3","1/2",1024,"52859441013204941216977989165824362837993054019925908927384477194798606179162062866795656036760758841784961286215917321059991272827351929193004525102909193/37377269190167522339457370469648760903867691713248359781530654205930946101551198857017808314217921196177539741081431327359978396389819954978801148797109325","49745681607429718634264588390953119759762323895917021547650382985744292497677614587570656266585962872861953341569673699669394815137245018415617591532712802/28720682667070963357924534322680015958968211660576346032633829680779466301631669358754238715055432912645437236197396265290926753299271695767364548361813951"},
	{"25/49","49/25",10,"5/7","7/5"},
	{"25/49","49/25",24,"5/7","7/5"},
	{"25/49","49/25",53,"5/7","7/5"},
	{"25/49","49/25",113,"5/7","7/5"},
	{"25/49","49/25",256,"5/7","7/5"},
	{"25/49","49/25",512,"5/7","7/5"},
	{"25/49","49/25",1024,"5/7","7/5"},
	{"41/7","43/7",10,"395/979","526/1273"},
	{"41/7","43/7",24,"91375/226471","28799/69698"},
	{"41/7","43/7",53,"571763809/1417104477","951527820/2302843363"},
	{"41/7","43/7",113,"1075189986272745529/2664835582786381345","437920551654940212/1059834946181476579"},
	{"41/7","43/7",256,"3272539648213141034592175632204410856710/8110920127585142778867214930688795673323","2203202465742239182571200542447245722363/5332088110234917116248245551724451252404"},
	{"41/7","43/7",512,"535465781015375912821825412529119240932963860827937005863341848164283307196080/1327140584298840802213089745813966169138115102922331447970902582247478803704449","974879304205468978216359230540656986091510497068856651328192775537288746609157/2359357538716652788251621238954097909383246530162422240718796252182189816262284"},
	{"41/7","43/7",1024,"1421276738977562250956368090435471881243145172650510923084412106358084351697851966943402905878645912526244317245662554284927640541726268187616752326422719840/3522604260986137139267045320950560518503705068092781547515318483782122068754081840747729592344913510690972694216154002875050312180986312515242400170684787201","190872663802708695046122618674487638798237956417431520423898330293169277702964181372734409402521800314557577562759306990807416216791536238314947657292715013/461941141159906454348335615954482867722905039032387131693505708388318491595297788105642129260026939500564237015917818848066087912000877948915797366796737804"},
	{"7927/13967553600","7933/13967553600",10,"147287/111","4684437/3529"},
	{"7927/13967553600","7933/13967553600",24,"44243158/33343","25300473/19060"},
	{"7927/13967553600","7933/13967553600",53,"10713783655182/8074235759","1645774581826/1239837039"},
	{"7927/13967553600","7933/13967553600",113,"34477525702845555875199/25983320166924560792","4657025933368405262213/3508349993695641956"},
	{"7927/13967553600","7933/13967553600",256,"23820160632097486787712621918151372673579179/17951603182483562966454812457172677332793","2116883956234777445343749719605684128518261/1594745213097608602961226011566379642341"},
	{"7927/13967553600","7933/13967553600",512,"377697750268705348794905699856419614643923255932660765360686238287376497671142169/284644601707857359974248867840522790413854648550899092975626950326691676364322","509800258280869426272124677413232496790923253315571262580053802278743612666028630/384055781203706842608377129913581391619717531551876913051928239672279679055997"},
	{"7927/13967553600","7933/13967553600",1024,"601190107928979802989116552651159434453867328357697611276508148160768234763944225591947449125398097921182670888482601443923965050645267523649474043140237161894/453075292877451561194493209214296031516575333931126669170922673777298395499536741259009362490552586901846001260617511202893124899571179952137210595375170043","486264310240680237926328179434210510275580872371228543488683677991225479897004714519123491298962509366567532314475294690153613872508840770866122077556822210157/366325078317391905839785004350788893455370564926366227773566985028124356264923698067932189988692809222251965671705930134391815133541996406448547252727910829"},
	{"13967553601/13967553600","13967553637/13967553600",10,"3020011591/3020011595","55870214401/55870214403"},
	{"13967553601/13967553600","13967553637/13967553600",24,"3020011591/3020011595","55870214401/55870214403"},
	{"13967553601/13967553600","13967553637/13967553600",53,"3020011591/3020011595","55870214401/55870214403"},
	{"13967553601/13967553600","13967553637/13967553600",113,"1324933144017182481/1324933145772054082","3121480857269578003201/3121480857381318432005"},
	{"13967553601/13967553600","13967553637/13967553600",256,"108948263752647293593356556836172436275033/108948263896949075838830341636284337765981","9743642742474817406737353348817471700544001/9743642742823613016238376477233816681152009"},
	{"13967553601/13967553600","13967553637/13967553600",512,"165595091015395241743968816039219108481942549104567784128247451068912426054711/165595091234725646300712792411510706516279149651317661668131108697209158089955","94938573894681450826619248927205388952098451975471762280608271361808830758933081318401/94938573898079990635801802589360599392473263971390049803922466227986161769084266777617"},
	{"13967553601/13967553600","13967553637/13967553600",1024,"812549336704065211407409881118923847710839133605248155385283686141256291866295707454391349572888449146158005235617130643644770748934168096121771933067371605/812549337780285367746754086069092284155961240423417205992407878729668995704101638582509437302255895966176669810976142824285357481469184651992091210326666392","161326261404047234176152634094948760355208121906253772145123412408832397026517921578736911805520398163213257162584522653621336864070754493171542320824764918528001/161326261409822270593451928223576792598284394839084013760085760692278285090853298117383742461712303381993634577555097068158407499778193574715761943034182838016031"},
	{NULL,NULL,0,NULL,NULL}}; /* test_table */

/* End of file tests/test_mpri_rsqrt_table.c */
