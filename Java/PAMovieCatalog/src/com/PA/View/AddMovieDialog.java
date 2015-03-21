package com.PA.View;


import java.awt.FlowLayout;
import java.util.*;

import javax.swing.*;
import javax.swing.border.EmptyBorder;

import com.PA.MovieCatalog.*;
import com.jgoodies.forms.layout.FormLayout;
import com.jgoodies.forms.layout.ColumnSpec;
import com.jgoodies.forms.factories.FormFactory;
import com.jgoodies.forms.layout.RowSpec;


public class AddMovieDialog extends JDialog 
{
	private List<MovieCategory> categoriesList;
	private final JPanel contentPanel = new JPanel();
	private JTextField movieNameTF;
	private JTextField imdbRatingTF;
	private JTextField yearTF;
	private JTextField dirNameTF;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			AddMovieDialog dialog = new AddMovieDialog();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 */
	public AddMovieDialog() {
		setBounds(100, 100, 450, 300);
		getContentPane().setLayout(new BorderLayout());
		getContentPane().setLayout(null);
		getContentPane().setLayout(new FormLayout(new ColumnSpec[] {
				ColumnSpec.decode("1px"),
				FormFactory.UNRELATED_GAP_COLSPEC,
				ColumnSpec.decode("71px"),
				ColumnSpec.decode("86px"),
				FormFactory.RELATED_GAP_COLSPEC,
				ColumnSpec.decode("default:grow"),},
			new RowSpec[] {
				RowSpec.decode("1px"),
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("20px"),
				FormFactory.LINE_GAP_ROWSPEC,
				RowSpec.decode("20px"),
				FormFactory.LINE_GAP_ROWSPEC,
				RowSpec.decode("20px"),
				FormFactory.LINE_GAP_ROWSPEC,
				RowSpec.decode("20px"),
				FormFactory.RELATED_GAP_ROWSPEC,
				RowSpec.decode("default:grow"),}));
		contentPanel.setBounds(0, 0, 0, 0);
		contentPanel.setLayout(new FlowLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, "1, 1, fill, fill");
		
		JLabel lblMovieName = new JLabel("Movie name:");
		lblMovieName.setBounds(10, 11, 61, 14);
		getContentPane().add(lblMovieName, "3, 3, left, center");
		
		movieNameTF = new JTextField();
		movieNameTF.setBounds(81, 8, 86, 20);
		getContentPane().add(movieNameTF, "4, 3, left, top");
		movieNameTF.setColumns(10);
		
		JLabel lblImdbRating = new JLabel("IMDB rating:");
		lblImdbRating.setBounds(10, 36, 61, 14);
		getContentPane().add(lblImdbRating, "3, 5, left, center");
		
		imdbRatingTF = new JTextField();
		imdbRatingTF.setColumns(10);
		imdbRatingTF.setBounds(81, 33, 86, 20);
		getContentPane().add(imdbRatingTF, "4, 5, left, top");
		
		JLabel lblYear = new JLabel("Year:");
		lblYear.setBounds(10, 61, 61, 14);
		getContentPane().add(lblYear, "3, 7, fill, center");
		
		yearTF = new JTextField();
		yearTF.setBounds(81, 58, 86, 20);
		getContentPane().add(yearTF, "4, 7, left, top");
		yearTF.setColumns(10);
		
		JLabel lblDirectorName = new JLabel("Director name:");
		lblDirectorName.setBounds(10, 86, 71, 14);
		getContentPane().add(lblDirectorName, "3, 9, left, center");
		
		dirNameTF = new JTextField();
		dirNameTF.setColumns(10);
		dirNameTF.setBounds(81, 83, 86, 20);
		getContentPane().add(dirNameTF, "4, 9, left, top");
	}
}
