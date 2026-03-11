/**
 * BeamVR / Trinus Session Logger
 * Version: 2026.1.0
 * Port: 45517 Monitoring
 */

// 1. Core Webhook: Receives data from Shadow PC or Phone
function doGet(e) {
  const ss = SpreadsheetApp.getActiveSpreadsheet();
  const sheet = ss.getSheetByName("VR_Performance_Logs") || ss.insertSheet("VR_Performance_Logs");
  
  // Set up Headers if the sheet is empty
  if (sheet.getLastRow() === 0) {
    sheet.appendRow(["Timestamp", "Device", "Software", "Port", "Latency (ms)", "Bitrate (kbps)", "Connection"]);
    sheet.getRange("A1:G1").setFontWeight("bold").setBackground("#d9ead3");
  }

  // Extract parameters from the incoming URL (e.g., ?software=Trinus&latency=22)
  const timestamp  = new Date();
  const device     = e.parameter.device || "Shadow PC";
  const software   = e.parameter.software || "Trinus/BeamVR";
  const port       = e.parameter.port || "45517";
  const latency    = e.parameter.latency || "0";
  const bitrate    = e.parameter.bitrate || "0";
  const connection = e.parameter.conn || "USB-Tether";

  // Append data to the next available row
  sheet.appendRow([timestamp, device, software, port, latency, bitrate, connection]);

  // Return success message to the sender (Phone/PC)
  return ContentService.createTextOutput("SUCCESS: Data Beamed to Google Sheets")
    .setMimeType(ContentService.MimeType.TEXT);
}

// 2. Dashboard Logic: Get average latency for your Shadow PC session
function getSessionSummary() {
  const sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("VR_Performance_Logs");
  const lastRow = sheet.getLastRow();
  if (lastRow < 2) return "No data yet.";

  const data = sheet.getRange(2, 5, lastRow - 1, 1).getValues(); // Column E (Latency)
  const sum = data.reduce((acc, val) => acc + Number(val[0]), 0);
  const avg = sum / data.length;

  Logger.log("Average Latency on Port 45517: " + avg.toFixed(2) + "ms");
  return avg;
}
