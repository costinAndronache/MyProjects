package com.PA.SPA;

import java.util.*;

public class Student 
{
	private String name;
	private List<Project> preferredProjectsList;
	Project currentlyAssignedProject;
	
	Student(Project[] preferredProjects, String name)
	{
		this.name = name;
		preferredProjectsList = new ArrayList<Project>(Arrays.asList(preferredProjects));
		currentlyAssignedProject = null;
	}
	
	public String getName()
	{
		return this.name;
	}
	
	public List<Project> getListOfPreferredProjects()
	{
		return this.preferredProjectsList;
	}
	
	public void removePreferredProject(Project p)
	{
		this.preferredProjectsList.remove(p);
	}
	
	
	public void setCurrentlyAssignedProject(Project p)
	{
		this.currentlyAssignedProject = p;
	}
	
	public Project getCurrentlyAssignedProject()
	{
		return this.currentlyAssignedProject;
	}
	
	public Project getMostPreferredProject()
	{
		if(this.preferredProjectsList.size() >= 1)
		return this.preferredProjectsList.get(0);
		else
			return null;
	}
	
	@Override
	public String toString()
	{
		String res = "Student: ";
		
		res += this.name + ", prefers:\n";
		for(Project p : this.preferredProjectsList)
		{
			res += p.toString() + " ";
		}
		
		if(this.currentlyAssignedProject != null)
		{
			res += "\nAnd I am assigned to " + this.currentlyAssignedProject.toString();
		}
		
		return res;
	}
}
