package cjFastChatServer;

import java.awt.BorderLayout;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class HelpDialog extends JDialog {

	private final JPanel contentPanel = new JPanel();

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			HelpDialog dialog = new HelpDialog();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 */
	public HelpDialog() {
		setBounds(100, 100, 513, 266);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(null);
		
		JLabel lblInOrderTo = new JLabel("In order to be the host user, your router must be configured to allow port forwarding ");
		lblInOrderTo.setBounds(10, 0, 485, 29);
		contentPanel.add(lblInOrderTo);
		
		JLabel lblThereIsNo = new JLabel("There is no standard way to do this, as each router has it's own configuration page.");
		lblThereIsNo.setBounds(10, 41, 485, 14);
		contentPanel.add(lblThereIsNo);
		
		JLabel lblForThePort = new JLabel("for the port 8556.");
		lblForThePort.setBounds(10, 23, 379, 14);
		contentPanel.add(lblForThePort);
		
		JLabel lblToGetIn = new JLabel("To get in to that page one usually types 192.168.x.x in the address bar.");
		lblToGetIn.setBounds(10, 55, 485, 24);
		contentPanel.add(lblToGetIn);
		
		JLabel lblAgainThisMight = new JLabel("Again, this might be different for your router. ");
		lblAgainThisMight.setBounds(10, 79, 485, 24);
		contentPanel.add(lblAgainThisMight);
		
		JLabel lblAUserConnected = new JLabel("A user connected directly to the internet shouldn't have any problems hosting.");
		lblAUserConnected.setBounds(10, 198, 485, 29);
		contentPanel.add(lblAUserConnected);
		
		JLabel lblAlsoThereIs = new JLabel("Also, there is a high chance that users still cannot connect to you, even after ");
		lblAlsoThereIs.setBounds(10, 113, 485, 29);
		contentPanel.add(lblAlsoThereIs);
		
		JLabel lblTheRouterIs = new JLabel("the router is set up to allow port forwarding.");
		lblTheRouterIs.setBounds(10, 136, 379, 14);
		contentPanel.add(lblTheRouterIs);
		
		JLabel lblInThatCase = new JLabel("In that case, you should give them the router's WAN IP, which you can find on");
		lblInThatCase.setBounds(10, 153, 485, 29);
		contentPanel.add(lblInThatCase);
		
		JLabel lblItsConfigurationPage = new JLabel("it's configuration page.");
		lblItsConfigurationPage.setBounds(10, 177, 379, 24);
		contentPanel.add(lblItsConfigurationPage);
		{
			JPanel buttonPane = new JPanel();
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			buttonPane.setLayout(null);
			{
				JButton okButton = new JButton("OK");
				okButton.setBounds(388, 5, 49, 23);
				okButton.setActionCommand("OK");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
		}
		
		setVisible(true);
	}
}
