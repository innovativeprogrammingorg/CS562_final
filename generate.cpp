#include "generate.h"
using namespace std;

int main(int argc,char** argv){
	int entries = 3000;
	srand((unsigned) time(NULL));
	if(argc == 2){
		entries = atoi(argv[1]);
	}
	
	string stmt = "INSERT INTO `";
	stmt += TABLE;
	stmt += "` (cust,prod,day,month,year,state,quant) VALUES (?,?,?,?,?,?,?)";
	SQLConn* conn = new SQLConn(DATABASE);
	string customers[424] = {"JAMES","JOHN","ROBERT","MICHAEL","WILLIAM","DAVID","RICHARD","CHARLES","JOSEPH","THOMAS","CHRISTOPHER","DANIEL","PAUL",
		"MARK","DONALD","GEORGE","KENNETH","STEVEN","EDWARD","BRIAN","RONALD","ANTHONY","KEVIN","JASON","MATTHEW","GARY","TIMOTHY","JOSE","LARRY",
		"JEFFREY","FRANK","SCOTT","ERIC","STEPHEN","ANDREW","RAYMOND","GREGORY","JOSHUA","JERRY","DENNIS","WALTER","PATRICK","PETER","HAROLD","DOUGLAS",
		"HENRY","CARL","ARTHUR","RYAN","ROGER","JOE","JUAN","JACK","ALBERT","JONATHAN","JUSTIN","TERRY","GERALD","KEITH","SAMUEL","WILLIE","RALPH",
		"LAWRENCE","NICHOLAS","ROY","BENJAMIN","BRUCE","BRANDON","ADAM","HARRY","FRED","WAYNE","BILLY","STEVE","LOUIS","JEREMY","AARON","RANDY",
		"HOWARD","EUGENE","CARLOS","RUSSELL","BOBBY","VICTOR","MARTIN","ERNEST","PHILLIP","TODD","JESSE","CRAIG","ALAN","SHAWN","CLARENCE","SEAN",
		"PHILIP","CHRIS","JOHNNY","EARL","JIMMY","ANTONIO","DANNY","BRYAN","TONY","LUIS","MIKE","STANLEY","LEONARD","NATHAN","DALE","MANUEL",
		"RODNEY","CURTIS","NORMAN","ALLEN","MARVIN","VINCENT","GLENN","JEFFERY","TRAVIS","JEFF","CHAD","JACOB","LEE","MELVIN","ALFRED","KYLE","FRANCIS"
		,"BRADLEY","JESUS","HERBERT","FREDERICK","RAY","JOEL","EDWIN","DON","EDDIE","RICKY","TROY","RANDALL","BARRY","ALEXANDER","BERNARD","MARIO",
		"LEROY","FRANCISCO","MARCUS","MICHEAL","THEODORE","CLIFFORD","MIGUEL","OSCAR","JAY","JIM","TOM","CALVIN","ALEX","JON","RONNIE","BILL","LLOYD"
		,"TOMMY","LEON","DEREK","WARREN","DARRELL","JEROME","FLOYD","LEO","ALVIN","TIM","WESLEY","GORDON","DEAN","GREG","JORGE","DUSTIN","PEDRO",
		"DERRICK","DAN","LEWIS","ZACHARY","COREY","HERMAN","MAURICE","VERNON","ROBERTO","CLYDE","GLEN","HECTOR","SHANE","RICARDO","SAM","RICK","LESTER"
		,"BRENT","RAMON","CHARLIE","TYLER","GILBERT","GENE","MARC","REGINALD","RUBEN","BRETT","ANGEL","NATHANIEL","RAFAEL","LESLIE","EDGAR","MILTON",
		"RAUL","BEN","CHESTER","CECIL","DUANE","FRANKLIN","ANDRE","ELMER","BRAD","GABRIEL","RON","MITCHELL","ROLAND","ARNOLD","HARVEY","JARED","ADRIAN",
		"KARL","CORY","CLAUDE","ERIK","DARRYL","JAMIE","NEIL","JESSIE","CHRISTIAN","JAVIER","FERNANDO","CLINTON","TED","MATHEW","TYRONE","DARREN",
		"LONNIE","LANCE","CODY","JULIO","KELLY","KURT","ALLAN","NELSON","GUY","CLAYTON","HUGH","MAX","DWAYNE","DWIGHT","ARMANDO","FELIX","JIMMIE",
		"EVERETT","JORDAN","IAN","WALLACE","KEN","BOB","JAIME","CASEY","ALFREDO","ALBERTO","DAVE","IVAN","JOHNNIE","SIDNEY","BYRON","JULIAN","ISAAC",
		"MORRIS","CLIFTON","WILLARD","DARYL","ROSS","VIRGIL","ANDY","MARSHALL","SALVADOR","PERRY","KIRK","SERGIO","MARION","TRACY","SETH","KENT",
		"TERRANCE","RENE","EDUARDO","TERRENCE","ENRIQUE","FREDDIE","WADE","AUSTIN","STUART","FREDRICK","ARTURO","ALEJANDRO","JACKIE","JOEY","NICK",
		"LUTHER","WENDELL","JEREMIAH","EVAN","JULIUS","DANA","DONNIE","OTIS","SHANNON","TREVOR","OLIVER","LUKE","HOMER","GERARD","DOUG","KENNY","HUBERT",
		"ANGELO","SHAUN","LYLE","MATT","LYNN","ALFONSO","ORLANDO","REX","CARLTON","ERNESTO","CAMERON","NEAL","PABLO","LORENZO","OMAR","WILBUR","BLAKE",
		"GRANT","HORACE","RODERICK","KERRY","ABRAHAM","WILLIS","RICKEY","JEAN","IRA","ANDRES","CESAR","JOHNATHAN","MALCOLM","RUDOLPH","DAMON","KELVIN",
		"RUDY","PRESTON","ALTON","ARCHIE","MARCO","WM","PETE","RANDOLPH","GARRY","GEOFFREY","JONATHON","FELIPE","BENNIE","GERARDO","ED","DOMINIC","ROBIN",
		"LOREN","DELBERT","COLIN","GUILLERMO","EARNEST","LUCAS","BENNY","NOEL","SPENCER","RODOLFO","MYRON","EDMUND","GARRETT","SALVATORE","CEDRIC","LOWELL",
		"GREGG","SHERMAN","WILSON","DEVIN","SYLVESTER","KIM","ROOSEVELT","ISRAEL","JERMAINE","FORREST","WILBERT","LELAND","SIMON","GUADALUPE","CLARK","IRVING",
		"CARROLL","BRYANT","OWEN","RUFUS","WOODROW","SAMMY","KRISTOPHER","MACK","LEVI","MARCOS","GUSTAVO","JAKE","LIONEL","MARTY","TAYLOR","ELLIS","DALLAS"};


	string products[16] = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P"};
	string states[50] = {"AK","AL","AZ","AR","CA","CO","CT","DE","FL","GA","HI","ID","IL","IN","IA","KS","KY","LA","ME","MD","MA","MI","MN","MS","MO","MT","NE","NV","NH",
				"NJ","NM","NY","NC","ND","OH","OK","OR","PA","RI","SC","SD","TN","TX","UT","VT","VA","WA","WV","WI","WY"};
	string customer;
	string product;
	int day = 0;
	int month = 0;
	int year = 0;
	string state;
	int quant = 0;
	
	for(int i = 0;i<entries;i++){

		customer = customers[rand()%424];
		product = products[rand()%16];
		day = rand()%28 + 1;
		month = rand()%12 + 1;
		year = 1996 + rand()%22;
		state = states[rand()%50];
		quant = rand()%1000 + 1;
		conn->execute("ssiiisi",stmt,customer,product,day,month,year,state,quant);

	}
	delete conn;
	return 0;
}