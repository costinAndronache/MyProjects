/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package paminiteleport;

import java.io.*;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jsoup.Jsoup;
import org.jsoup.parser.*;
import org.jsoup.helper.*;
import org.jsoup.nodes.*;
import org.jsoup.select.Elements;
/**
 *
 * @author Costinel
 */
public class PaMiniTeleport {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        if(args.length != 2)
        {
            System.out.println("USAGE: programName baseURL recursionDepth");
            
            for(String s : args)
                System.out.println(s);
            return;
        }
        
        String baseURL = args[0];
        int recursionDepth = Integer.parseInt(args[1]);
        
        try {
            String basePath = downloadAndPath(baseURL, 1, recursionDepth);
            System.out.println("File saved to path " + basePath);
        } catch (Exception ex) {
            Logger.getLogger(PaMiniTeleport.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        Scanner s = new Scanner(System.in);
        
        s.nextLine();
    }
    
    
    
    
    public static String downloadAndPath(String url, int step, int maxStep) 
    {
        Document doc = null;
        Elements links = null;
        try{
        doc = Jsoup.connect(url).get();
        links = doc.select("a[href]");
        }catch(Exception e)
        {
            return null;
        }
        if(step == maxStep)
        {
            String path;
            try {
                path = saveStringToFile(doc.toString(), doc.title());
            } catch (Exception ex) {
                return null;
            }
            return path;
        }
        
        for(Element link : links)
        {
            String newURL = link.attr("abs:href");
            String path = downloadAndPath(newURL, step + 1, maxStep);
            if(path != null)
            {
                link.attr("abs:href", path);
                link.attr("href", path);
            }
        }
        
       String path;
        try {
            path = saveStringToFile(doc.toString(), doc.title());
        } catch (Exception ex) {
            return null;
        }
       return path;
    }
    
    
    
    public static String saveStringToFile(String string, String title) throws Exception
    {
        File file = new File(title + ".html");
        file.createNewFile();
        
        BufferedWriter fileWriter = new BufferedWriter(new FileWriter(file));
        fileWriter.write(string);
        fileWriter.flush();
        fileWriter.close();
        
        return file.getAbsolutePath();
    }
    
}
