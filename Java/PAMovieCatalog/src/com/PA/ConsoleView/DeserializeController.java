package com.PA.ConsoleView;

import java.io.InputStreamReader;
import java.util.Scanner;

import com.PA.MovieCatalog.MovieDatabase;

public class DeserializeController extends MenuController {

	@Override
	public void runWithDatabase(MovieDatabase db) {
		// TODO Auto-generated method stub
		
		Scanner s = new Scanner(new InputStreamReader(System.in));
		String filename;
		System.out.println("Please insert the filename:" );
		filename = s.nextLine();

		boolean excep = false;
		try 
		{
			db.deserializeFromFile(filename);
		} catch (Exception e) 
		{
			excep = true;
			// TODO Auto-generated catch block
			System.out.println("Could not read from file. Reason: " + e.getMessage());
		}
		
		if(!excep)
		{
			System.out.println("Reading succesfull.");
		}		
		
	}

}
