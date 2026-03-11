/**
 * BeamVR / Trinus Performance Logger (2026)
 * Target Sheet: 1nJoL2Rho6kyOrbE3RE8O0hKRJ6POAE6ZwIgSCLfMJW8
 * Port: 45517 Monitoring
 */

const SPREADSHEET_ID = "1nJoL2Rho6kyOrbE3RE8O0hKRJ6POAE6ZwIgSCLfMJW8";

/**
 * 1. Main Entry Point: Handles Dashboard View and Data Logging
 */
function doGet(e) {
  // If no parameters are passed, show the HTML Dashboard
  if (Object.keys(e.parameter).length === 0) {
    return HtmlService.createHtmlOutputFromFile('index')
        .setTitle('BeamVR Real-Time Monitor')
        .setXFrameOptionsMode(HtmlService.XFrameOptionsMode.ALLOWALL)
        .addMetaTag('viewport', 'width=device-width, initial-scale=1');
  }
  
  // Otherwise, handle the data logging from Shadow PC/Phone
  return handleLogging(e);
}

/**
 * 2. Data Logging Logic (Triggered via Webhook URL)
 */
function handleLogging(e) {
  const ss = SpreadsheetApp.openById(SPREADSHEET_ID);
  const sheet = ss.getSheets()[0]; // Targets the first sheet (gid=1220979327)

  const timestamp = new Date();
  const software  = e.parameter.soft || "Trinus CBVR";
  const port      = e.parameter.port || "45517";
  const latency   = e.parameter.lag  || "0";
  const bitrate   = e.parameter.bit  || "0";
  const conn      = e.parameter.conn || "USB-Tether";
  const status    = "ACTIVE";

  sheet.appendRow([timestamp, software, port, conn, latency, bitrate, status]);

  return ContentService.createTextOutput("SUCCESS: Data Beamed to Shadow Sheet")
    .setMimeType(ContentService.MimeType.TEXT);
}

/**
 * 3. Initialize Sheet Columns (Triggered by Dashboard Button)
 */
function setupSheet() {
  const ss = SpreadsheetApp.openById(SPREADSHEET_ID);
  const sheet = ss.getSheets()[0];
  
  const headers = ["Timestamp", "Software", "Port", "Connection", "Latency_ms", "Bitrate_kbps", "Status"];
  
  sheet.clear(); // Clear to reset headers
  sheet.appendRow(headers);
  
  // Apply Professional Styling
  const range = sheet.getRange(1, 1, 1, headers.length);
  range.setBackground("#181a20")
       .setFontColor("#f0b90b")
       .setFontWeight("bold")
       .setHorizontalAlignment("center");
  
  sheet.setFrozenRows(1);
  return "Initialization Complete";
}

/**
 * 4. Fetch Data for Chart.js (Triggered by index.html polling)
 */
function getLatestLogs() {
  const ss = SpreadsheetApp.openById(SPREADSHEET_ID);
  const sheet = ss.getSheets()[0];
  const lastRow = sheet.getLastRow();
  
  if (lastRow < 2) return [];

  // Get the last 15 entries
  const startRow = Math.max(2, lastRow - 14);
  const numRows = lastRow - startRow + 1;
  const data = sheet.getRange(startRow, 1, numRows, 7).getValues();

  return data.map(row => ({
    time: Utilities.formatDate(new Date(row[0]), "GMT-5", "HH:mm:ss"), // Adjusted for your timezone
    latency: row[4],
    bitrate: row[5]
  }));
}

