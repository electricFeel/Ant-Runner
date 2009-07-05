package liquidware.runner;

import org.apache.tools.ant.Main;


public class AntRunner {
	public void run(String args[]){
		Main.main(args);
		//currently just a wrapper but lets keep this stub just in case we need some
		//type of preprocessing
	}
	
	public static void main(String args[]){
		AntRunner runner = new AntRunner();
		runner.run(args);
	}
}
