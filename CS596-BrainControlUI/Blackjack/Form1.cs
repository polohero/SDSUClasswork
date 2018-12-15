using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Threading.Tasks;
using System.ServiceModel;

using Emotiv;
using Games.Common.Cards;
using Games.Common.Decks;
using Games.Common.Hands;
using Games.Common.Engine;
using Games.Common.WCF;

namespace Games.BlackjackClient
{
    public partial class Form1 : Form
    {
        #region Constructors

        bool _trainingResult = false;
        bool _hasTrained = false;
        bool _trainingComplete = false;
        bool _wait = false;

        public Form1()
        {
            InitializeComponent();

            _player = Config.PlayerName;


            join();

            _refreshTask = Task.Factory.StartNew(() => runUpdate());

            startEmotiv();
        }

        #endregion

        #region Helper Methods

        private void startEmotiv()
        {
            if (true == Config.UseEmotiv)
            {
                try
                {
                    connectEmotiv();
                    train();

                    _emotivTask = Task.Factory.StartNew(() => processEmotive());

                    _connected = true;
                }
                catch (Exception exception)
                {
                    MessageBox.Show(
                        "Unable to connect to remote Emotiv system. The application will continue to run, but you will be unable to use the headset." +
                        "\n\nError:" + exception.Message,
                        "Error",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error);
                    _connected = false;
                    _emotivTask = Task.Factory.StartNew(() => processEmotive());
                }
            }
            else
            {
                _connected = false;
                _emotivTask = Task.Factory.StartNew(() => processEmotive());
            }
        }

        private void connectEmotiv()
        {
            _emotiv = EmoEngine.Instance;
            _emotiv.CognitivTrainingSucceeded +=
                new EmoEngine.CognitivTrainingSucceededEventHandler(engine_CognitivTrainingSucceeded);
            _emotiv.CognitivTrainingFailed +=
                new EmoEngine.CognitivTrainingFailedEventHandler(engine_CognitivTrainingFailed);
            _emotiv.CognitivTrainingCompleted +=
                new EmoEngine.CognitivTrainingCompletedEventHandler(engine_CognitivTrainingCompleted);
            _emotiv.EmoStateUpdated +=
                new EmoEngine.EmoStateUpdatedEventHandler(engine_EmoStateUpdated);

            _emotiv.Connect();
            // _emotiv.RemoteConnect("127.0.0.1", 1726);
        }

        private void train()
        {
            MessageBox.Show("Train Think NEUTRAL.");
            trainNeutral(EdkDll.EE_CognitivAction_t.COG_NEUTRAL);

            MessageBox.Show("Train Think STAY.");
            train(EdkDll.EE_CognitivAction_t.COG_PUSH,
                 ((uint)EdkDll.EE_CognitivAction_t.COG_PUSH));

            MessageBox.Show("Train Think HIT.");
            train(EdkDll.EE_CognitivAction_t.COG_LEFT,
                 ((uint)EdkDll.EE_CognitivAction_t.COG_PUSH | (uint)EdkDll.EE_CognitivAction_t.COG_LEFT));

            _trainingComplete = true;

        }

        private void trainNeutral(EdkDll.EE_CognitivAction_t action)
        {
            _emotiv.CognitivSetTrainingAction(0, action);
            _emotiv.CognitivSetTrainingControl(0, EdkDll.EE_CognitivTrainingControl_t.COG_START);

            Thread.Sleep(10000);
            _hasTrained = true;
            _emotiv.ProcessEvents(1000);

            if (false == _trainingResult)
            {
                MessageBox.Show("Train again");
                trainNeutral(action);
            }

        }

        private void train(EdkDll.EE_CognitivAction_t action, uint activeActions)
        {
            _emotiv.CognitivSetTrainingAction(0, action);
            _emotiv.CognitivSetActiveActions(0, activeActions);
            _emotiv.CognitivSetTrainingControl(0, EdkDll.EE_CognitivTrainingControl_t.COG_START);

            Thread.Sleep(10000);
            _hasTrained = true;
            _emotiv.ProcessEvents(1000);

            if (false == _trainingResult)
            {
                _emotiv.CognitivSetTrainingControl(0, EdkDll.EE_CognitivTrainingControl_t.COG_REJECT);
                _emotiv.ProcessEvents(1000);
                MessageBox.Show("Train again");
                train(action, activeActions);
            }
        }

        void engine_CognitivTrainingSucceeded(object sender, EmoEngineEventArgs e)
        {
            _emotiv.CognitivSetTrainingControl(0, EdkDll.EE_CognitivTrainingControl_t.COG_ACCEPT);
            Thread.Sleep(10000);
            _emotiv.ProcessEvents();
            _trainingResult = true;
            MessageBox.Show("Trained action");
        }

        void engine_CognitivTrainingCompleted(object sender, EmoEngineEventArgs e)
        {
            _trainingResult = false;

        }

        void engine_CognitivTrainingFailed(object sender, EmoEngineEventArgs e)
        {
            MessageBox.Show("Failed!!!");
            _trainingResult = false;
        }




        /// <summary>
        /// Processes any emotiv events.
        /// If it was unable to connect it will just spin
        /// until the task is completed.
        /// </summary>
        private void processEmotive()
        {
            while (true == _running)
            {
                if (true == _connected && false == _wait)
                {
                    if (false == _running) { break; }
                    try
                    {
                        Thread.Sleep(3000);
                        if (false == _running) { break; }
                        if (false == _wait)
                        {
                            _emotiv.ProcessEvents(1000);
                        }
                    }
                    catch (Exception exception)
                    {
                        handleError(exception);
                    }
                }
                else
                {
                    Thread.Sleep(2000);
                }
            }

            closeEmotive();
        }

        /// <summary>
        /// Closes the emotive. It will not throw an
        /// exception since the form is closing.
        /// </summary>
        private void closeEmotive()
        {
            try
            {
                if (true == _connected)
                {
                    _emotiv.Disconnect();
                }
            }
            catch (Exception)
            {
                //Swallow
            }
        }

        /// <summary>
        /// Updates the form with the newest version of the
        /// info. This is so that if another user finishes
        /// their turn, the current client will get updated.
        /// </summary>
        private void runUpdate()
        {
            while (true == _running)
            {
                try
                {
                    if (true == _running)
                    {
                        BlackjackResponse response =
                            new BlackjackEngineProxy().Get(
                                new BlackjackTable(_table, _table, null, null),
                                new BlackjackPlayer(_player));

                        processResponse(response);
                    }

                    Thread.Sleep(1000);
                }
                catch (Exception exception)
                {
                    handleError(exception);
                }
            }

        }

        /// <summary>
        /// Updates some control to be enabled, or disabled.
        /// </summary>
        /// <param name="control"></param>
        /// <param name="enabled"></param>
        private void updateControlEnabled(Control control, bool enabled)
        {
            if (true == InvokeRequired)
            {
                Invoke(
                    new UpdateControlEnabled(updateControlEnabled),
                    control,
                    enabled);
            }
            else
            {
                control.Enabled = enabled;
            }
        }

        /// <summary>
        /// Processes a BlackjackResponse and updates the form
        /// with the newest info.
        /// </summary>
        /// <param name="response"></param>
        private void processResponse(BlackjackResponse response)
        {
            if (response.Result == BlackjackResult.Success)
            {
                try
                {
                    if (response.Table != null &&
                        response.Table.History.Count > _previousHistory)
                    {
                        _previousHistory = response.Table.History.Count;

                        BlackjackPlayer player =
                            ((BlackjackPlayer)response.Table.Get(new Player(_player)));
                        if (null != player)
                        {

                            refreshListbox(response.Table.History.ToArray(), listBoxHistory);
                            refreshListbox(player.Hand.Cards.ToArray(), listBoxCards);
                            refreshListbox(response.Table.Dealer.Hand.Cards.ToArray(), listBoxDealer);

                            updateLabel(player.Hand.Value.ToString(), labelValue);
                            updateLabel(response.Table.Dealer.Hand.Value.ToString(), labelDealter);

                            if (response.Table.State == TableState.Waiting &&
                               response.Table.Owner.Equals(new Player(_player)))
                            {
                                updateControlEnabled(
                                    buttonHit, false);
                                updateControlEnabled(
                                    buttonStay, false);
                                updateControlEnabled(
                                    buttonStart, true);
                            }
                            else if (response.Table.State == TableState.Stopped)
                            {
                                updateControlEnabled(
                                    buttonHit, false);
                                updateControlEnabled(
                                    buttonStay, false);
                                if (response.Table.Owner.Equals(new Player(_player)))
                                {
                                    updateControlEnabled(
                                        buttonStart, true);
                                }
                                else
                                {
                                    updateControlEnabled(
                                        buttonStart, false);
                                }
                            }
                            else if (player.State == PlayerStateEnum.Turn)
                            {
                                updateControlEnabled(
                                    buttonHit, true);
                                updateControlEnabled(
                                    buttonStay, true);
                                updateControlEnabled(
                                    buttonStart, false);
                            }
                            else
                            {
                                updateControlEnabled(
                                    buttonHit, false);
                                updateControlEnabled(
                                    buttonStay, false);
                                updateControlEnabled(
                                    buttonStart, false);
                            }

                            if (null != player)
                            {
                                updateLabel(player.State.ToString(), labelCurrentState);

                            }
                        }
                    }
                }
                catch (Exception)
                {
                    // Swallow
                }
            }
            if (response.Result == BlackjackResult.Failure)
            {
                throw new Exception(response.Message);
            }
        }

        /// <summary>
        /// Updates the text on a label.
        /// </summary>
        /// <param name="data"></param>
        /// <param name="label"></param>
        private void updateLabel(string data, Label label)
        { 
            if (true == InvokeRequired)
            {
                Invoke(
                    new UpdateLabel(updateLabel),
                    data,
                    label);
            }
            else
            {
                label.Text = data;
            }
        }

        private void updateLabel(string data, Color foreColor, Label label)
        {
            if (true == InvokeRequired)
            {
                Invoke(
                    new UpdateLabelColor(updateLabel),
                    data,
                    foreColor,
                    label);
            }
            else
            {
                label.Text = data;
                label.ForeColor = foreColor;
            }
        }

        /// <summary>
        /// Clears a listbox and adds all the new items
        /// to it.
        /// </summary>
        /// <param name="data"></param>
        /// <param name="listBox"></param>
        private void refreshListbox(object[] data, ListBox listBox)
        {
            if (true == InvokeRequired)
            {
                Invoke(
                    new RefreshListbox(refreshListbox),
                    data,
                    listBox);
            }
            else
            {
                listBox.Items.Clear();
                foreach (object s in data)
                {
                    listBox.Items.Add(s.ToString());
                }

                if (listBox.Items.Count > 0)
                {
                    listBox.TopIndex = listBox.Items.Count - 1;
                }
            }
        }

        /// <summary>
        /// Sends a join request to join the table.
        /// </summary>
        private bool join()
        {
            try
            {
                processResponse(new BlackjackEngineProxy().Join(
                         new BlackjackTable(_table, _table, null, null),
                          new BlackjackPlayer(_player)));
                return true;
            }
            catch (Exception exception)
            {
                handleError(exception);
                return false;
            }
        }

        /// <summary>
        /// Pops a messagebox up with the exception message.
        /// </summary>
        /// <param name="exception"></param>
        /// <param name="message"></param>
        private void handleError(Exception exception, string message = "")
        {
            MessageBox.Show(
                exception.Message,
                string.IsNullOrEmpty(message) ? "Error" : message,
                MessageBoxButtons.OK,
                MessageBoxIcon.Error);
        }

        /// <summary>
        /// Sends a start request to the service.
        /// </summary>
        private void start()
        {
            try
            {
                processResponse(new BlackjackEngineProxy().Start(
                         new BlackjackTable(_table, _table, null, null),
                          new BlackjackPlayer(_player)));
            }
            catch (Exception exception)
            {
                handleError(exception);
            }
        }

        /// <summary>
        /// Sends a stay request to the service.
        /// </summary>
        private void stay()
        {
            try
            {
                processResponse(new BlackjackEngineProxy().Stay(
                         new BlackjackTable(_table, _table, null, null),
                          new BlackjackPlayer(_player)));
            }
            catch (Exception exception)
            {
                handleError(exception);
            }
        }

        /// <summary>
        /// Sends a hit request to the service.
        /// </summary>
        private void hit()
        {
            try
            {
                processResponse(new BlackjackEngineProxy().Hit(
                         new BlackjackTable(_table, _table, null, null),
                          new BlackjackPlayer(_player)));
            }
            catch (Exception exception)
            {
                handleError(exception);
            }
        }

        /// <summary>
        /// Tells the service if the user is leaving the table.
        /// </summary>
        private void leave()
        {
            BlackjackResponse response = new BlackjackEngineProxy().LeaveTable(
                     new BlackjackTable(_table, _table, null, null),
                      new BlackjackPlayer(_player));

            if (response.Result == BlackjackResult.Failure)
            {
                throw new Exception(response.Message);
            }
        }

        /// <summary>
        /// Sends a chat request
        /// </summary>
        private void chat(string message)
        {
            try
            {
                processResponse(new BlackjackEngineProxy().Chat(
                         new BlackjackTable(_table, _table, null, null),
                          new BlackjackPlayer(_player),
                          message));
            }
            catch (Exception exception)
            {
                handleError(exception);
            }
        }

        #endregion

        #region Control Methods

        private void textBoxChat_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == Convert.ToChar(Keys.Return))
            {
                chat(textBoxChat.Text);
                textBoxChat.Text = string.Empty;
            }
        }

        /// <summary>
        /// Handles any event changes with the emotiv engine.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void engine_EmoStateUpdated(object sender, EmoStateUpdatedEventArgs e)
        {
            if (false == _trainingComplete)
            {
                return;
            }

            _wait = true;

            try
            {

                EdkDll.EE_CognitivAction_t action =
                    e.emoState.CognitivGetCurrentAction();

                updateLabel(
                    "Current Emotiv State: " +
                        Enum.GetName(typeof(EdkDll.EE_CognitivAction_t), action),
                        Color.Empty,
                    labelEmotivState);

                if (EdkDll.EE_CognitivAction_t.COG_LEFT == action)
                {
                    updateLabel(
                          "Current Emotiv State: " +
                              Enum.GetName(typeof(EdkDll.EE_CognitivAction_t), action),
                              Color.Blue,
                          labelEmotivState);
                    if (true == buttonHit.Enabled)
                    {
                        if (DialogResult.Yes == MessageBox.Show("Did you try to HIT?", "Hit?", MessageBoxButtons.YesNo))
                        {
                            hit();
                        }
                    }
                }
                else if (EdkDll.EE_CognitivAction_t.COG_PUSH == action)
                {
                    updateLabel(
                          "Current Emotiv State: " +
                              Enum.GetName(typeof(EdkDll.EE_CognitivAction_t), action),
                              Color.Green,
                          labelEmotivState);
                    if (true == buttonStay.Enabled)
                    {
                        if (DialogResult.Yes == MessageBox.Show("Did you try to STAY?", "Stay?", MessageBoxButtons.YesNo))
                        {
                            stay();
                        }
                    }
                    else if (true == buttonStart.Enabled)
                    {
                        if (DialogResult.Yes == MessageBox.Show("Are you ready to START?", "Start?", MessageBoxButtons.YesNo))
                        {
                            start();
                        }
                    }
                }
            }
            catch (Exception exception)
            {
                //handleError(exception);
            }
            finally
            {
                _wait = false;
            }
        }

        /// <summary>
        /// Handles the form closing event.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            try
            {
                leave();
                _running = false;
                Task.WaitAll(_refreshTask);

                Thread.Sleep(3000);
            }
            catch (Exception exception)
            {
                handleError(exception);
                _running = true;
                e.Cancel = true;
            }
        }

        /// <summary>
        /// Handles a "Restart" button event.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonStart_Click(object sender, EventArgs e)
        {
            start();
        }

        /// <summary>
        /// Handles a stay button event.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonStay_Click(object sender, EventArgs e)
        {
            stay();
        }

        /// <summary>
        /// Handles a hit button event.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonHit_Click(object sender, EventArgs e)
        {
            hit();
        }

        /// <summary>
        /// NOT USED
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonEvaluate_Click(object sender, EventArgs e)
        {
            try
            {
                processResponse(new BlackjackEngineProxy().Evaluate(
                         new BlackjackTable(_table, _table, null, null),
                          new BlackjackPlayer(_player)));
            }
            catch (Exception exception)
            {
                handleError(exception);
            }
        }

        /// <summary>
        /// NOT USED.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonJoin_Click(object sender, EventArgs e)
        {
            join();
        }

        private void buttonChat_Click(object sender, EventArgs e)
        {
            chat(
                true == string.IsNullOrEmpty(textBoxChat.Text) ? string.Empty : textBoxChat.Text);
        }

        #endregion

        #region Private Attributes

        private string _player = DateTime.Now.Ticks.ToString();
        private string _table = "1";
        private bool _running = true;
        private EmoEngine _emotiv;
        private bool _connected = false;
        private Task _emotivTask;
        private Task _refreshTask;
        private int _previousHistory = 0;

        private delegate void RefreshListbox(object[] data, ListBox listBox);
        private delegate void UpdateLabel(string data, Label label);
        private delegate void UpdateLabelColor(string data, Color foreColor, Label label);
        private delegate void UpdateControlEnabled(Control control, bool enabled);

        #endregion
    }
}
