package com.PA.ConsoleView;

import java.util.*;

public class MenuControllerFactory 
{
	private static MenuControllerFactory sharedInstance;
	private Map<String, MenuController> menuControllerMap;
	
	public static MenuControllerFactory getSharedInstance()
	{
		if(sharedInstance == null)
		{
			sharedInstance = new MenuControllerFactory();
		}
		
		return sharedInstance;
	}
	
	private MenuControllerFactory()
	{
		this.menuControllerMap = new HashMap<String, MenuController>();
	}
	
	public void registerControllerForMenu(MenuController mc, String menuName)
	{
		this.menuControllerMap.put(menuName, mc);
	}
	
	public MenuController getControllerForMenu(String menuName)
	{
		return this.menuControllerMap.get(menuName);
	}
}
