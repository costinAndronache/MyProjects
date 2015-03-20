package cjFastChatServer;

import java.awt.BorderLayout;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.UnknownHostException;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import cjFastChatCommon.Utilities;

public class ServerDialog extends JDialog {

	private final JPanel contentPanel = new JPanel();

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			ServerDialog dialog = new ServerDialog();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 * @throws UnknownHostException 
	 */
	public ServerDialog() throws UnknownHostException {
		setAlwaysOnTop(true);
		setResizable(false);
		setBounds(100, 100, 403, 218);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		{
			JLabel lblHelloAndWelcome = new JLabel("Hello and welcome to cjFastChat.");
			lblHelloAndWelcome.setHorizontalAlignment(SwingConstants.CENTER);
			lblHelloAndWelcome.setBounds(-12, 11, 420, 26);
			contentPanel.add(lblHelloAndWelcome);
		}
		{
			JLabel lblThisIsThe = new JLabel("This is the server and it is currently running");
			lblThisIsThe.setHorizontalAlignment(SwingConstants.CENTER);
			lblThisIsThe.setBounds(-23, 29, 420, 26);
			contentPanel.add(lblThisIsThe);
		}
		{
			JLabel lblTheUsersMust = new JLabel("The users must insert these paramterers in order to connect:");
			lblTheUsersMust.setHorizontalAlignment(SwingConstants.CENTER);
			lblTheUsersMust.setBounds(20, 46, 388, 37);
			contentPanel.add(lblTheUsersMust);
		}
		{
			JLabel lblIpAddress = new JLabel("IP address: " + Utilities.getExternalIP());
			lblIpAddress.setBounds(43, 81, 200, 20);
			contentPanel.add(lblIpAddress);
		}
		{
			JLabel lblPort = new JLabel("Port: " + 8556);
			lblPort.setBounds(314, 81, 63, 20);
			contentPanel.add(lblPort);
		}
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setBounds(10, 122, 440, 1);
			contentPanel.add(buttonPane);
			{
				JButton cancelButton = new JButton("Cancel");
				cancelButton.setBounds(368, 5, 67, 23);
				cancelButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						System.exit(0);
					}
				});
				buttonPane.setLayout(null);
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
		
		JButton btnCloseServer = new JButton("Close server");
		btnCloseServer.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		btnCloseServer.setBounds(43, 120, 152, 23);
		contentPanel.add(btnCloseServer);
		
		JLabel lblAuthorAndronacheCostin = new JLabel("Author: Andronache Costin");
		lblAuthorAndronacheCostin.setFont(new Font("Tahoma", Font.PLAIN, 12));
		lblAuthorAndronacheCostin.setBounds(239, 161, 211, 20);
		contentPanel.add(lblAuthorAndronacheCostin);
		
		JLabel lblinfouaicIb = new JLabel("@InfoUAIC IB7");
		lblinfouaicIb.setFont(new Font("Tahoma", Font.PLAIN, 12));
		lblinfouaicIb.setBounds(239, 174, 138, 20);
		contentPanel.add(lblinfouaicIb);
		{
			JButton btnIAmUsing = new JButton("I am using a router");
			btnIAmUsing.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent e) {
					HelpDialog hd = new HelpDialog();
					
				}
			});
			btnIAmUsing.setBounds(43, 154, 152, 28);
			contentPanel.add(btnIAmUsing);
		}
		
		setVisible(true);
	}
}
