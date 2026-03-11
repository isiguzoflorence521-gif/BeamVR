/**
 * BeamVR Session Logger
 * Receives telemetry from Shadow PC/Mobile via Webhook
 */

function doGet(e) {
  const ss = SpreadsheetApp.getActiveSpreadsheet();
  const sheet = ss.getSheetByName("Session_Logs") || ss.insertSheet("Session_Logs");
  
  // Setup headers if sheet is new
  if (sheet.getLastRow() === 0) {
    sheet.appendRow(["Timestamp", "Software", "Connection", "Latency_ms", "Bitrate_kbps", "Status"]);
  }

  // Extract parameters from the VR software/Shadow PC ping
  const software = e.parameter.software || "Unknown"; // Trinus, VRidge, iVRy
  const connection = e.parameter.conn || "USB";       // USB, Wi-Fi
  const latency = e.parameter.latency || 0;
  const bitrate = e.parameter.bitrate || 0;

  // Append data to Google Sheet
  sheet.appendRow([new Date(), software, connection, latency, bitrate, "ACTIVE"]);

  return ContentService.createTextOutput("Success: BeamVR Data Logged").setMimeType(ContentService.MimeType.TEXT);
}

function getAverageLatency() {
  const sheet = SpreadsheetApp.getActiveSpreadsheet().getSheetByName("Session_Logs");
  const data = sheet.getDataRange().getValues();
  let total = 0;
  
  for (let i = 1; i < data.length; i++) {
    total += parseFloat(data[i][3]); // Latency column
  }
  
  return total / (data.length - 1);
}
