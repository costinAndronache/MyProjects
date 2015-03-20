package com.PA.SPA;

import java.util.*;

public class Project 
{
	private String name;
	private int capacity;
	private Lecturer lecturer;
	List<Student> assignedStudents;
	
	
	Project(String name, int capacity)
	{
		this.name = name;
		this.capacity = capacity;
		lecturer = null;
		assignedStudents = new ArrayList<Student>();
	}
	
	
	
	public String getName()
	{
		return this.name;
	}
	
	public boolean isFull()
	{
		return this.capacity == this.assignedStudents.size();
	}
	
	public boolean isOverSubscribed()
	{
		return this.capacity < this.assignedStudents.size();
	}
	
	public Lecturer getLecturer()
	{
		return this.lecturer;
	}
	
	public void setLecturer(Lecturer lecturer)
	{
		this.lecturer = lecturer;
	}
	
	public void assignNewStudent(Student s)
	{
		this.assignedStudents.add(s);
	}
	
	public void removeAssignedStudent(Student s)
	{
		this.assignedStudents.remove(s);
	}
	
	@Override
	public String toString()
	{
		return this.name;
	}
}

