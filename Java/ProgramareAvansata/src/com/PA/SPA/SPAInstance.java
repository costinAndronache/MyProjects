package com.PA.SPA;

import java.util.*;

public class SPAInstance 
{
	private List<Student> studentList;
	private List<Project> projectList;
	private List<Lecturer> lecturerList;
	
	SPAInstance(List<Student> studentList, 
					   List<Project> projectList,
					   List<Lecturer> lecturerList)
					   
	{
		this.studentList = studentList;
		this.projectList = projectList;
		this.lecturerList = lecturerList;
	}
	
	public List<Student> solve()
	{
		while(true)
		{
			Student si = this.getUnassignedStudent();
			if(si == null)
				{
					break;
				}
			
			Project pj = si.getMostPreferredProject();
			
			if(pj == null)
				break;
			
			Lecturer lk = pj.getLecturer();
			
			this.assignStudentToProject(si, pj);
			
			if(pj.isOverSubscribed())
			{
				Student sr = lk.getWorstStudentFromProject(pj);
				if(sr == null)
					break;
				this.breakAssignment(sr, pj);
			}
			else
				if(lk.isOverSubscribed())
				{
					Student sr = lk.getWorstStudent();
					 if(sr == null)
						 break;
					 
					this.breakAssignment(sr, sr.getCurrentlyAssignedProject());
				}
			
			if(pj.isFull())
			{
				Student sr = lk.getWorstStudentFromProject(pj);
				if(sr == null)
					break;
				
				List<Student> list = lk.getSuccesorOfStudentFromProjectedPreferredListOfProject(sr, pj);
				for(Student s :list )
				{
					s.removePreferredProject(pj);
					lk.removeStudentFromProjectedPreferredList(s, pj);
				}
				
			}
			
			if(lk.isFull())
			{
				Student sr = lk.getWorstStudent();
				List<Student> succList = lk.getSuccesorOfStudentFromPreferredList(sr);
				for(Student s : succList)
				{
					for(Project p : s.getListOfPreferredProjects())
					{
						if(lk.getListOfProjects().contains(p))
						{
							s.removePreferredProject(p);
							lk.removeStudentFromProjectedPreferredList(s, p);
							
						}
					}
				}
			}
		
		}
		
		
		return this.studentList;
	}
	
	private Student getUnassignedStudent()
	{
		for(Student s : this.studentList)
		{
			if (s.getCurrentlyAssignedProject() == null)
				{
				   return s;
				}
		}
		
		return null;
	}
	
	private void assignStudentToProject(Student s, Project p)
	{
		Lecturer lec = p.getLecturer();
		s.setCurrentlyAssignedProject(p);
		p.assignNewStudent(s);
		lec.addStudentForProject(s, p);
	}
	
	private void breakAssignment(Student s, Project p)
	{
		s.setCurrentlyAssignedProject(null);
		p.removeAssignedStudent(s);
		p.getLecturer().removeStudentForProject(s, p);
	}

	
	@Override
	public String toString()
	{
		String res = "Problem description:\n1.Project List:";
		for(Project p : this.projectList)
		{
			res += p.toString() + "\n";
		}
		
		res +="2.Student List:\n";
		for(Student s : this.studentList)
		{
			res += s.toString() +"\n";
		}
		
		res +="3.Lecturers List:\n";
		for(Lecturer lec : this.lecturerList)
		{
			res += lec.toString() +"\n";
		}
		
		return res;
	}
	
	public static void main(String[] args)
	{
		Project p1, p2, p3;
		Student s1, s2, s3;
		Lecturer lec1, lec2, lec3;
		
		p1 = new Project("Proj1", 1);
		p2 = new Project("Proj2", 1);
		p3 = new Project("Proj3", 1);
		
		s1 = new Student(new Project[]{p1}, "S1");
		s2 = new Student(new Project[]{p2}, "S2");
		s3 = new Student(new Project[]{p3}, "S3");
		
		lec1 = new Lecturer(  new Student[]{s1}, new Project[]{p1}, "Lec1", 1);
		lec2 = new Lecturer(  new Student[]{s2}, new Project[]{p2}, "Lec2", 1);
		lec3 = new Lecturer(  new Student[]{s3}, new Project[]{p3}, "Lec3", 1);
		
		p1.setLecturer(lec1);
		p2.setLecturer(lec2);
		p3.setLecturer(lec3);
		
		Student[] studs = {s2, s3, s1};
		Project[] projs = {p1, p2, p3};
		Lecturer[] lecs = {lec1, lec2, lec3};
		
		SPAInstance spa = new SPAInstance(Arrays.asList(studs), Arrays.asList(projs), Arrays.asList(lecs));
		
		System.out.println(spa.toString());
		
		System.out.println(spa.solve());
	}
	
}
