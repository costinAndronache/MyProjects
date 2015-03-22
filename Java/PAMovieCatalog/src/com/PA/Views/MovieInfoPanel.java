package com.PA.Views;

import javax.swing.JPanel;

import java.awt.FlowLayout;

import javax.swing.JLabel;

import java.awt.Color;

import javax.swing.SwingConstants;
import javax.swing.JButton;

import com.PA.MovieCatalog.Movie;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class MovieInfoPanel extends JPanel 
{
	private JLabel lblActualMovieName;
	private JLabel lblActualRating;
	private JLabel lblActualIMDBID;
	private JLabel lblActualDirectorName;
	private JButton btnOpenVideo;
	
	public void populateWithMovie(Movie movie)
	{
		this.lblActualMovieName.setText(movie.getName());
		this.lblActualIMDBID.setText(movie.getImdbID());
		this.lblActualRating.setText(movie.getRating() + " ");
		this.lblActualDirectorName.setText(movie.getDirectorName());
		
	}

	/**
	 * Create the panel.
	 */
	public MovieInfoPanel() {
		setBackground(Color.GRAY);
		setLayout(null);
		
		JPanel panel_4 = new JPanel();
		panel_4.setBounds(0, 0, 160, 156);
		add(panel_4);
		FlowLayout fl_panel_4 = new FlowLayout(FlowLayout.LEFT, 5, 5);
		fl_panel_4.setAlignOnBaseline(true);
		panel_4.setLayout(fl_panel_4);
		
		JPanel panel = new JPanel();
		panel_4.add(panel);
		FlowLayout fl_panel = new FlowLayout(FlowLayout.LEFT, 5, 5);
		fl_panel.setAlignOnBaseline(true);
		panel.setLayout(fl_panel);
		
		JLabel lblName = new JLabel("Name:");
		panel.add(lblName);
		
		lblActualMovieName = new JLabel("MovieName");
		panel.add(lblActualMovieName);
		
		JPanel panel_2 = new JPanel();
		panel_4.add(panel_2);
		FlowLayout flowLayout_1 = (FlowLayout) panel_2.getLayout();
		flowLayout_1.setAlignment(FlowLayout.LEFT);
		flowLayout_1.setAlignOnBaseline(true);
		
		JLabel lblRating = new JLabel("Rating:");
		lblRating.setHorizontalAlignment(SwingConstants.LEFT);
		panel_2.add(lblRating);
		
		lblActualRating = new JLabel("actual");
		panel_2.add(lblActualRating);
		
		JPanel panel_1 = new JPanel();
		panel_4.add(panel_1);
		FlowLayout flowLayout_2 = (FlowLayout) panel_1.getLayout();
		flowLayout_2.setAlignment(FlowLayout.LEFT);
		flowLayout_2.setAlignOnBaseline(true);
		
		JLabel lblImdbId = new JLabel("IMDB id:");
		panel_1.add(lblImdbId);
		
		lblActualIMDBID = new JLabel("12345");
		panel_1.add(lblActualIMDBID);
		lblActualIMDBID.setBackground(Color.RED);
		
		JPanel panel_3 = new JPanel();
		panel_4.add(panel_3);
		FlowLayout flowLayout = (FlowLayout) panel_3.getLayout();
		flowLayout.setAlignment(FlowLayout.LEFT);
		flowLayout.setAlignOnBaseline(true);
		
		JLabel lblDirectorName = new JLabel("Director name:");
		lblDirectorName.setHorizontalAlignment(SwingConstants.LEFT);
		panel_3.add(lblDirectorName);
		
		lblActualDirectorName = new JLabel("actual director");
		panel_3.add(lblActualDirectorName);
		
		btnOpenVideo = new JButton("Open");
		btnOpenVideo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
			}
		});
		panel_4.add(btnOpenVideo);

	}
}
