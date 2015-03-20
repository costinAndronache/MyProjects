package com.PA.SPA;
import java.util.*;
public class Lecturer 
{
	private String name; 
	int capacity;
	private Map<Project, List<Student>> assignedStudentsPerProject;
	private Map<Project, List<Student>> projectedPreferenceListPerProject;
	List<Student> currentlyAssignedStudents;
	List<Student> preferredStudentsList;
	List<Project> projectList;
	
	Lecturer(Student[] listOfPreferredStudents, Project[] listOfProjects, String name, int capacity)
	{
		this.name = name;
		this.capacity = capacity;
		
		assignedStudentsPerProject = new HashMap<Project, List<Student>>();
		projectedPreferenceListPerProject = new HashMap<Project, List<Student>>();
		currentlyAssignedStudents = new ArrayList<Student>();
		
		preferredStudentsList = new ArrayList<Student>(Arrays.asList(listOfPreferredStudents));
		projectList = new ArrayList<Project>(Arrays.asList(listOfProjects));
		
		for(Student s : preferredStudentsList)
		{
			List<Project> preferredProjectsByThisStudent = s.getListOfPreferredProjects();
			for(Project p : preferredProjectsByThisStudent)
			{
				if(this.projectList.contains(p))
				{
					this.getOrCreateProjectedListForProject(p).add(s);
				}
			}
			
		}
	}
	

	
	public String getName()
	{
		return this.name;
	}
	
	public  void addStudentForProject(Student s, Project p)
	{
		this.getOrCreatedStudentListPerProject(p).add(s);
		this.currentlyAssignedStudents.add(s);
	}
	
	public void removeStudentForProject(Student s, Project p)
	{
		this.getOrCreatedStudentListPerProject(p).remove(s);
		this.currentlyAssignedStudents.remove(s);
	}
	
	public void removeStudentFromProjectedPreferredList(Student s, Project p)
	{
		this.getOrCreateProjectedListForProject(p).remove(s);
	}
	
	public boolean isFull()
	{
		return this.capacity == this.currentlyAssignedStudents.size();
	}
	
	public boolean isOverSubscribed()
	{
		return this.capacity < this.currentlyAssignedStudents.size();
	}
	
	
	public Student getWorstStudent()
	{
		return this.getWorsStudentFromList(this.currentlyAssignedStudents);
	}
	
	public Student getWorstStudentFromProject(Project p)
	{
		return this.getWorsStudentFromList(this.getOrCreatedStudentListPerProject(p));
	}
	
	public List<Student> getSuccesorOfStudentFromProjectedPreferredListOfProject(Student s, Project p)
	{
		return this.getSuccesorListOfStudentFromList(s, this.getOrCreateProjectedListForProject(p));
	}
	
	public List<Student> getSuccesorOfStudentFromPreferredList(Student s)
	{
		return this.getSuccesorListOfStudentFromList(s, preferredStudentsList);
	}
	
	public List<Student> getOrCreateProjectedListForProject(Project p)
	{
		List<Student> res = this.projectedPreferenceListPerProject.get(p);
		
		if(res == null)
		{
			res = new ArrayList<Student>();
			this.projectedPreferenceListPerProject.put(p, res);
		}
		
		return res;
	}
	
	public List<Student> getListOfPreferredStudents()
	{
		return this.preferredStudentsList;
	}
	
	public List<Project> getListOfProjects()
	{
		return this.projectList;
	}
	
	private List<Student> getOrCreatedStudentListPerProject(Project p)
	{
		List<Student> list = this.assignedStudentsPerProject.get(p);
		
		if(list == null)
		{
			list = new ArrayList<Student>();
			this.assignedStudentsPerProject.put(p, list);
		}
		
		return list;
	}
	
	private Student getWorsStudentFromList(List<Student> list)
	{
		
		if(list == this.preferredStudentsList)
		{
			return this.preferredStudentsList.get(list.size()-1);
		}
		
		Student res=null;
		int maxPos = -1;
		for(Student s : list)
		{
			 int pos = this.preferredStudentsList.indexOf(s);
			 if(pos > maxPos)
			 {
				 maxPos = pos;
				 res = s;
			 }
		}
		
		return res;
	}
	
	private List<Student> getSuccesorListOfStudentFromList(Student s, List<Student> list)
	{
		List<Student> alist = new ArrayList<Student>();
		
		for(int i= list.indexOf(s)+1; i<list.size(); i++)
		{
			alist.add(list.get(i));
		}
		
		return alist;
	}
	
	@Override
	public String toString()
	{
		String res = "Lecturer: " + this.name + ", gives the following projects:\n";
		for(Project p : this.projectList)
		{
			res +=" " + p.toString();
		}
		
		res += "\nPrefers the following students:\n";
		for(Student s : preferredStudentsList)
		{
			res += s.getName() + " ";
		}
		
		return res;
	}
}
